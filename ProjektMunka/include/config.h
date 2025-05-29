#ifndef CONFIG_H
#define CONFIG_H

#ifdef _WIN32
  #define PATH_SEP "\\\\"
#else
  #define PATH_SEP "/"
#endif

#define ASSET_DIR "assets"

#define ASSET_PATH(sub) (ASSET_DIR PATH_SEP sub)

#endif // CONFIG_H