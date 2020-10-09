#include "kunParser.h"
#include "IntrusiveHashMap.h"

namespace kun
{
	struct Context
	{		
		Parser parser;

		void startWithFile(const char* fileName);
		struct FileData
		{

		};
		enum LoadStatus
		{
			DirtyOrNotLoaded,
			Failed,
			Succeed,
		};
		struct TranslationUnit
		{
			std::string sourceFileName;
			std::set<std::string> dependees;// if the binary interface changed, which file must be recompiled?
			std::set<std::string> dependencies;

			LoadStatus sourceLoadedStatus;
			std::string source;

			LoadStatus astLoadedStatus;
			std::shared_ptr<peg::Ast> ast;
			template<int n>
			std::string getName()
			{
				return sourceFileName;
			}

		};
		const char* getSource(TranslationUnit* unit);
		std::shared_ptr<peg::Ast> getAST(TranslationUnit* unit);

		const char* getSource(const char* fileName);
		std::shared_ptr<peg::Ast> getAST(const char* fileName);
		// void getLLVMModule() {}
		// void getJITModule() {}

		// void getJITDylib() {}
		TranslationUnit* getTranslationUnit(const char* fileName);

		// TODO: using memory mapped file to deal with large source files.
		bool loadFile(const char* fileName, std::string& target);

	protected:
		IntrusiveHashMap<TranslationUnit>translationUnitMap;
	};
	/*enum DataType
	{
		Source,
		AST,
		LLVMModule,
		JITDylib,

	};
	template<DataType d>
	T* getData(const char * fileName)
	{

	}*/
}
