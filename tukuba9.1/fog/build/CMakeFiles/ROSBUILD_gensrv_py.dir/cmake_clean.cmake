FILE(REMOVE_RECURSE
  "../srv_gen"
  "../srv_gen"
  "../src/fog/srv"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/fog/srv/__init__.py"
  "../src/fog/srv/_FOG.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
