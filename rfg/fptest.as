FPCLAC= 6550
FPLOAD= 6551
FPSTOR= 6552
FPADD= 6553
FPMULT= 6554

*200
Main, FPCLAC
	cla
	tad k
loop, dca k
	FPLOAD
aptr, a
	FPMULT
bptr, b
	FPSTOR
cptr, c
	tad aptr
	tad d
	dca aptr
	tad bptr
	tad d
	dca bptr
	tad cptr
	tad d
	dca cptr
	tad k
	tad j
	sma
	jmp loop
	hlt

*250
d,11
k, 27
j, -1
a, 0
0
0
b, 0
0
0
c, 0
0
0
000
000
0111
201
300
1123
0
4000
0
377
0111
1111
201
5000
223
0
4000
0
201
5000
223
0
0
0
0
0
0
0177
3476
1700
0200
2464
3360
0201
2224
4114
0202
0726
7432
0201
3431
5565
0205
0511
2462
0200
3765
7224
0201
2451
6623
0203
2441
4305
0202
2100
1664
0202
0443
5526
0205
2776
7427
0202
2302
0025
0202
3214
6007
0206
1631
7702
0202
3207
4764
0201
2444
0773
0205
1756
7765
0201
2476
6070
0203
0763
7007
0206
0075
1420
0203
0377
2362
0202
3615
5470
0207
0277
0220
0202
3577
4442
0203
1047
3555
0207
0725
7526
0201
0231
5562
0203
2706
0430
0205
3316
5616
0200
2033
3474
0203
2125
0626
0205
0524
7676
0203
0265
0147
0200
2242
2737
0204
2700
2032
0203
3636
1653
0177
2413
5342
0204
2273
7547
0202
0161
6055
0203
1636
3407
0206
2103
5225
0203
2042
2121
0200
0432
0433
0204
2716
0576
0204
0070
2013
0204
0112
5210
0211
0204
7542
0203
0060
5122
0203
2573
0522
0207
2715
0336
0203
1025
3274
0203
3331
5243
0210
0533
7301
0201
1117
3061
0202
1116
1351
0204
2507
7736
0202
1721
5254
0204
0731
4654
0207
3215
2677
$Main