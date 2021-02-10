#include "llvm/ADT/PointerIntPair.h"
#include <vector>
#include <unordered_map>
namespace kun
{
	struct Reflection
	{
		enum Qualifiers
		{
			Const,
			Volatile,
			Restrict,
			Count,
		};
		struct PointerType;
		struct StaticArrayType;
		struct TypeBase
		{
			virtual ~TypeBase() {};

			PointerType* GetPointerType() {}
			StaticArrayType* GetStaticArrayType(int dimension, unsigned long long * arrayLength) {}
		protected:
			PointerType* pointerType = nullptr;

		};
		struct QualType
		{
			TypeBase* GetPointer(){}
		protected:
			llvm::PointerIntPair<TypeBase*, Count> value;
		};
		struct NamedType : TypeBase
		{
			std::string name;
		};
		struct TypeDef : NamedType
		{
			QualType target;
		};
		struct BasicType : NamedType
		{
		};
		struct IntType : public BasicType
		{
			int bits; // negate bits means signed type.
		};
		struct VoidType : public BasicType
		{
		};
		struct HalfType : public BasicType {};
		struct FloatType : public BasicType {};
		struct DoubleType : public BasicType {};
		struct VectorType : public TypeBase 
		{ 
			BasicType* elementType;
			int vectorLength; 
		};
		struct PointerType : public TypeBase 
		{
			TypeBase* pointeeType;
		};
		struct StaticArrayType : public TypeBase
		{
			TypeBase* elementType;
			std::vector<unsigned long long>dimensions;
		};
		//std::unordered_map< int, IntType*> intTypes;
		//std::unordered_map<BasicType*, VectorType*> vectorTypes;
		std::unordered_map<std::string, TypeBase> namedTypes; // Including typedefs.
	};
}