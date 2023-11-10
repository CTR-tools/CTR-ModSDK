add_custom_target(Valkyrie_D3D12_HLSL)

file(GLOB_RECURSE EMULATOR_SHADER_SRCS ${EMULATOR_SHADER_DIR}/*.hlsl ${EMULATOR_SHADER_DIR}/*.HLSL)

foreach(FILE ${EMULATOR_SHADER_SRCS})
  
  get_filename_component(FILE_WE ${FILE} NAME_WE)
  add_custom_command(TARGET Valkyrie_D3D12_HLSL
                     COMMAND dxc.exe /nologo /T vs_6_0 /O3 /Vn ${FILE_WE}_vs /Fh ${FILE_WE}_vs.h ${FILE} /DVERTEX /DD3D12
					 MAIN_DEPENDENCY ${FILE}
                     COMMENT "HLSL ${FILE}"
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     VERBATIM
			   )
  add_custom_command(TARGET Valkyrie_D3D12_HLSL
                     COMMAND dxc.exe /nologo /T ps_6_0 /O3 /Vn ${FILE_WE}_ps /Fh ${FILE_WE}_ps.h ${FILE} /DPIXEL /DD3D12
					 MAIN_DEPENDENCY ${FILE}
                     COMMENT "HLSL ${FILE}"
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     VERBATIM
			   )
endforeach(FILE)

set_target_properties(
Valkyrie_D3D12_HLSL PROPERTIES FOLDER "Libs/Emulator/ShaderLib"
)

add_dependencies(${PROJECT_NAME} Valkyrie_D3D12_HLSL)