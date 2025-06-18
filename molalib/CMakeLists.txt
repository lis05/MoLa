add_library(molalib SHARED

src/back/alloc.c
src/back/alloc.h
src/back/api.h
src/back/cmap.c
src/back/cmap.h
src/back/cmod.c
src/back/cmod.h
src/back/env.c
src/back/env.h
src/back/error.c
src/back/error.h
src/back/gc.c
src/back/gc.h
src/back/gen.c
src/back/gen.h
src/back/ident_map.c
src/back/ident_map.h
src/back/object.c
src/back/object.h
src/back/scope.c
src/back/scope.h
src/back/stat.c
src/back/stat.h
src/back/types.c
src/back/types.h
src/back/vm.c
src/back/vm.h
src/back/xmempool.c
src/back/xmempool.h

src/front/api.h
src/front/ast.c
src/front/ast.h
src/front/lex.yy.c
src/front/parser.c
src/front/parser.h
src/front/rules.tab.c
src/front/rules.tab.h
src/front/symtab.c
src/front/symtab.h

src/api.h
src/cvector.h
src/log.h
src/util.c
src/util.h

)