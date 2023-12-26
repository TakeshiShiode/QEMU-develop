MATLAB\R2021\extern\examples\shrlib

mex shrlibsample.c
loadlibrary('shrlibsample','shrlibsample.h')
x = [1,2;3,4];
y = calllib('shrlibsample','multDoubleArray', x, 4)
unloadlibrary('shrlibsample')