add_custom_target(Valkyrie_Vulkan_HLSL)

file(GLOB_RECURSE EMULATOR_SHADER_SRCS ${EMULATOR_SHADER_DIR}/*.hlsl ${EMULATOR_SHADER_DIR}/*.HLSL)

foreach(FILE ${EMULATOR_SHADER_SRCS})
  
  get_filename_component(FILE_WE ${FILE} NAME_WE)
  add_custom_command(TARGET Valkyrie_Vulkan_HLSL
                     COMMAND glslangValidator -D -DD3D12 --sub vert 0 --stb frag 2 --ssb frag 2 --spirv-val --vn ${FILE_WE}_vs -S vert -e main -o ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_WE}_vs.h --define-macro VERTEX -V ${FILE}
					 MAIN_DEPENDENCY ${FILE}
                     COMMENT "HLSL ${FILE}"
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     VERBATIM
			   )
  add_custom_command(TARGET Valkyrie_Vulkan_HLSL
                     COMMAND glslangValidator -D -DD3D12 --sub vert 0 --stb frag 2 --ssb frag 2 --spirv-val --vn ${FILE_WE}_ps -S frag -e main -o ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_WE}_ps.h --define-macro PIXEL -V ${FILE}
					 MAIN_DEPENDENCY ${FILE}
                     COMMENT "HLSL ${FILE}"
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     VERBATIM
			   )
endforeach(FILE)

set_target_properties(
Valkyrie_Vulkan_HLSL PROPERTIES FOLDER "Libs/Emulator/ShaderLib"
)

add_dependencies(${PROJECT_NAME} Valkyrie_Vulkan_HLSL)