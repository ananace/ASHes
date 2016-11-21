SET(ASH_HEADERS
	ashes/Ashes.hpp
	ashes/Engine.hpp
	ashes/Engine.inl
	ashes/EnumType.hpp
	ashes/EnumType.inl
	ashes/Function.hpp
	ashes/Function.inl
	ashes/IRefType.hpp
	ashes/ObjectType.hpp
	ashes/ObjectType.inl
	ashes/TypeStore.hpp
	ashes/TypeStore.inl
)

ADD_LIBRARY(ashes STATIC ${ASH_HEADERS})
SET_TARGET_PROPERTIES(ashes PROPERTIES
	LINKER_LANGUAGE CXX
)
