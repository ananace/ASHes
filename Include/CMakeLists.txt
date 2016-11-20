SET(ASH_HEADERS
	ASHes/Ashes.hpp
	ASHes/Engine.hpp
	ASHes/Engine.inl
	ASHes/EnumType.hpp
	ASHes/Function.hpp
	ASHes/Function.inl
	ASHes/IRefType.hpp
	ASHes/ObjectType.hpp
	ASHes/ObjectType.inl
	ASHes/TypeStore.hpp
	ASHes/TypeStore.inl
)

ADD_LIBRARY(ASHes STATIC ${ASH_HEADERS})
set_target_properties(ASHes PROPERTIES LINKER_LANGUAGE CXX)