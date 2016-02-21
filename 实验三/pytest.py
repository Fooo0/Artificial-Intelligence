def nim_func(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11):
    print p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11

    ls = [p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11]

    nim_sum = p1^p2^p3^p4^p5^p6^p7^p8^p9^p10^p11
  
    if nim_sum == 0:
		j = 1
        for x in ls:
            if x != 0:
                return(j,0)
            j += 1

    else:
		i = 1
    	for x in ls:
            if nim_sum^x < x:
                return (i,nim_sum^x)
            i += 1

    return (-1,-1)

