namespace kun
{
	struct Reflection
	{
		struct TypeBase
		{
			virtual ~TypeBase() {};
		};
		struct NamedType : TypeBase
		{
			std::string originalName;
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
		std::unordered_map< int, IntType*> intTypes;
		std::unordered_map<BasicType*, VectorType*> vectorTypes;
		std::unordered_map<std::string, TypeBase> namedTypes; // Including typedefs.
	};
}