@ECHO OFF

REM DevStudio stuff
DEL /s /q DP.ncb
DEL /s /q DP.aps
DEL /s /q DP.opt
DEL /s /q DP.plg
DEL /s /q DP.dsw

REM MIDL generated
DEL /s /q DP.tlb
DEL /s /q DP.h
DEL /s /q DP_i.c
DEL /s /q DP_p.c
DEL /s /q dlldata.c

REM Sourcesafe
DEL /s /q vssver.scc
DEL /s /q mssccprj.scc

REM Build output
RD /s /q Debug

DEL /s /q Release\*.obj
DEL /s /q Release\*.ilk
DEL /s /q Release\*.pch
DEL /s /q Release\*.pdb
DEL /s /q Release\*.idb
DEL /s /q Release\*.trg
DEL /s /q Release\*.tlh
DEL /s /q Release\*.res