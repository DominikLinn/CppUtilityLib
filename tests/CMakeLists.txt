add_executable(cpputility_dummy
	dummy.cpp
)

target_link_libraries(cpputility_dummy PUBLIC cpputility::cpputility)
set_target_properties(cpputility_dummy PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
	LINKER_LANGUAGE CXX
)
