#pragma once

namespace Graphics
{
	class GlResult
	{
	friend class GlErrorChecker;

	public:
		void print();
		void report();
		bool isOk() const { return this->isOk_; }
		~GlResult();
	
	private:
		char* log_ = nullptr;
		bool isOk_;

		GlResult(bool isOk);
		static GlResult makeSuccess();
		static GlResult makeFailure();
		static GlResult makeFailure(char* log);
	};
}