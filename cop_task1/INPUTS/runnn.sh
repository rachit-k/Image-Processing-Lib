for i in {16,32,64,128,256,512,1024}
do
	for j in {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}
	do
	touch input$i-$j
		./input_gen input$i-$j $i >> input$i-$j
	done
done	
