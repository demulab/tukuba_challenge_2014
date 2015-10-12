FILE(REMOVE_RECURSE
  "../srv_gen"
  "../srv_gen"
  "../src/readWayPoints/srv"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/readWayPoints/srv/__init__.py"
  "../src/readWayPoints/srv/_AllWayPoints.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
