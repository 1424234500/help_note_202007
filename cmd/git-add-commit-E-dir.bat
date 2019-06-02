::cmd

::echo ------------ git add commit push

%1%
cd %2%
git add . 
git commit -am "%date%"
cd /

::echo -------end