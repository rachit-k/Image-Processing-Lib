make
for k in {3,9,15}
do	
	for i in {16,32,64,128,256,512,1024}
	do
		touch pthreadout$i-$k
		for j in {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}
		do
			./output convolution_withoutpadding_matrixmult input$i-{$j} $i kernel$k $k pthread >> pthreadout$i-$k
		done
	done
done	