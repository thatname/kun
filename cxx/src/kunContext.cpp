#include "kunContext.h"

void kun::Context::startWithFile(const char* fileName)
{

}
kun::Context::TranslationUnit* kun::Context::getTranslationUnit(const char* filename)
{
	auto it = translationUnitMap.search(filename);
	if (!it)
	{
		it = new TranslationUnit;
		translationUnitMap.insert(it);

		auto& str = it->source;
		if (!loadFile(filename, str))
			return nullptr;
	}
	return it;
}

bool kun::Context::loadFile(const char* fileName, std::string& target)
{
	FILE* fp = fopen(fileName, "rb");
	if (!fp)
		return false;
	fseek(fp, 0, SEEK_END);
	auto l = ftell(fp);
	target.resize(l);
	fseek(fp, 0, SEEK_SET);
	auto len = fread(fp, l, 1, fp);
	fclose(fp);
	return (bool)len;
}


std::shared_ptr<peg::Ast> kun::Context::getAST(kun::Context::TranslationUnit* unit)
{
	if (unit->astLoadedStatus == DirtyOrNotLoaded)
	{
		unit->astLoadedStatus = Failed;
		auto source = getSource(unit);
		if (!source)
			return nullptr;

		auto success = parser.parse(unit->sourceFileName.c_str(), source);
		if (success)
			unit->astLoadedStatus = Succeed;
	}
	return unit->ast;
}

const char* kun::Context::getSource(TranslationUnit* unit)
{
	if (unit->sourceLoadedStatus == DirtyOrNotLoaded)
	{
		unit->sourceLoadedStatus = Failed;
		
		auto& str = unit->source;
		if (!loadFile(unit->sourceFileName.c_str(), str))
			return nullptr;

		unit->sourceLoadedStatus = Succeed;
	}
	return unit->source.c_str();
}

const char* kun::Context::getSource(const char* fileName)
{
	auto unit = getTranslationUnit(fileName);
	if (!unit)
		return nullptr;

	return getSource(unit);
}

std::shared_ptr<peg::Ast> kun::Context::getAST(const char* fileName)
{
	auto unit = getTranslationUnit(fileName);
	if (!unit)
		return nullptr;
	
	return getAST(unit);
}
