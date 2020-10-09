#include "peglib.h"
namespace kun
{
	class Parser
	{
	public:
		Parser();
		std::shared_ptr<peg::Ast> parse(const char* fileName, const char* source);
	protected:
		peg::parser parser;
	};
}