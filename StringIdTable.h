#pragma once
#include <new>
#include "StringId.h"

namespace Common
{
	template <typename V>
	class StringIdTable
	{
	public:
		StringIdTable(u32 capacity)
			: capacity_(capacity), size_(0)
		{
			// let the record show that this is some of the worst syntax I've ever seen
			this->buckets_ = static_cast<Bucket*>(
				::operator new[](
					capacity_ * sizeof(Bucket),
					std::align_val_t(alignof(Bucket)) // pass the requirement for Bucket's byte alignment
					)
				);
			this->control_ = new BucketMetadata[capacity];
		}

	private:
		// struct zone
		struct Bucket
		{
			StringId key;
			V value;

			Bucket(StringId key, const V& value) : key(key), value(value) {}
		};
		
		struct BucketMetadata
		{
		public:
			enum class State
			{
				Empty = 0x0,
				Full = 0x01,
				Dead = 0x02
			};
			
			inline void set(State state)
			{
				this->state = (u8)state;
			}

			inline bool is(State state)
			{
				return this->state == (u8)state;
			}

		private:
			u8 state = (u8)State::Empty;
		};

		struct SearchResult
		{
			SearchResult() {}
			SearchResult(V* item, u32 index) : item(item) {}

			V* item = nullptr;
			u32 index = 0;

			inline bool isEmpty()
			{
				return this->item == nullptr;
			}
		};

		// private field zone
		u32 size_;
		u32 capacity_;
		Bucket* buckets_;
		BucketMetadata* control_;

		// private methods zone
		SearchResult find(StringId stringId)
		{
			u32 index = stringId % this->capacity_;
			i32 offset = 1;
			bool toFlip = true;

			while (!this->control_[index].is(BucketMetadata::State::Empty))
			{
				// we found the key
				bool foundKey = this->control_[index].is(BucketMetadata::State::Full)
					&& this->buckets_[index].key == stringId;
				if (foundKey)
					return SearchResult(&this->buckets_[index].value, index);

				// perform a qudratic probe: (i +/- j^2)
				index = (index + offset) % this->capacity_;
				if (!toFlip)
					offset *= 2;
				else
					offset *= -1;
			}

			// we didn't find the key
			return SearchResult();
		}

		void destroyValues()
		{
			for (u32 i = 0; i < this->capacity_; i++)
			{
				if (this->control_[i].is(BucketMetadata::State::Full))
					this->buckets_[i].~Bucket();
			}
		}

	public:
		// public methods zone
		void add(StringId stringId, V value)
		{
			assert(this->size_ < this->capacity_);

			u32 index = stringId % this->capacity_;
			i32 offset = 1;
			bool toFlip = true;

			while (this->control_[index].is(BucketMetadata::State::Full))
			{
				// perform a qudratic probe: (i +/- j^2)
				index = (index + offset) % this->capacity_;
				if (!toFlip)
					offset *= 2;
				else
					offset *= -1;
			}

			// fill the bucket
			new (&buckets_[index]) Bucket(stringId, value);
			this->control_[index].set(BucketMetadata::State::Full);

			this->size_++;
		}

		V* get(StringId stringId)
		{
			SearchResult result = find(stringId);
			return result.item;
		}

		const V* get(StringId stringId) const
		{
			SearchResult result = find(stringId);
			return result.item;
		}

		inline V& at(StringId stringId)
		{
			V* value = get(stringId);
			assert(value != nullptr);
			return *value;
		}

		inline const V& at(StringId stringId) const
		{
			const V* value = get(stringId);
			assert(value != nullptr);
			return *value;
		}

		void remove(StringId stringId)
		{
			SearchResult result = find(stringId);

			assert(!result.isEmpty());

			this->buckets_[result.index].~Bucket();
			this->control_[result.index].set(BucketMetadata::State::Dead);
			this->size_--;
		}

		bool contains(StringId stringId) const
		{
			return !find(stringId).isEmpty();
		}

		void clear()
		{
			// call everybody's destructor
			destroyValues();

			// set all the metadata to Empty
			memset(this->control_, 0, this->capacity_);
		}

		~StringIdTable()
		{
			destroyValues();
			
			::operator delete[](
				buckets_,
				std::align_val_t(alignof(Bucket))
			);

			delete[] control_;
		}
	};
}
