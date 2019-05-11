
for i in 16 32 64 128 256 512 1024
do
	for j in  3 9 15
	do
		touch out$i-$j.dat
		paste mklout$i-$j openblasout$i-$j pthreadout$i-$j manualout$i-$j >> out$i-$j.dat
	done
done