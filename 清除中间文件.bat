@echo on 
echo 删除vc编译产生的临时文件
echo 删除开始...
for /r . %%c in (.) do @if exist "%%c\Debug" rd /S/Q "%%c\Debug"
for /r . %%c in (.) do @if exist "%%c\Release" rd /S/Q "%%c\Release"
for /r . %%c in (*.bsc *.aps *.clw *.ncb *.plg *.positions *.WW *.user *.opensdf *.sdf *.pdb *.ilk *.exp *.orig) do del "%%c"
if exist "ipch" rd /S/Q "ipch"
del /a:h *.suo
echo 删除完毕...
pause