
DPps.dll: dlldata.obj DP_p.obj DP_i.obj
	link /dll /out:DPps.dll /def:DPps.def /entry:DllMain dlldata.obj DP_p.obj DP_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del DPps.dll
	@del DPps.lib
	@del DPps.exp
	@del dlldata.obj
	@del DP_p.obj
	@del DP_i.obj
