#include "NumTheoryFormulas.h"




std::vector<std::vector<NumTheoryFormulas::SUPERLONG>> NumTheoryFormulas::EuclideanAlgorithm(NumTheoryFormulas::SUPERLONG a, NumTheoryFormulas::SUPERLONG b)
{/*
    if (GCD(a, mod) > 1)
    {
        return FAILPAIR(-1, false);
    }*/


    std::vector<std::vector<NumTheoryFormulas::SUPERLONG>> output = std::vector<std::vector<NumTheoryFormulas::SUPERLONG>>();
    //matrix format:  bigger, quotient, smaller, remainder, GCD

    NumTheoryFormulas::SUPERLONG bigger = std::max(a, b);
    NumTheoryFormulas::SUPERLONG smaller = std::min(a, b);

    NumTheoryFormulas::SUPERLONG quotient = bigger / smaller;
    NumTheoryFormulas::SUPERLONG remainder = bigger % smaller;

    output.push_back(std::vector<NumTheoryFormulas::SUPERLONG>());
    output.at(0).push_back(bigger);
    output.at(0).push_back(quotient);
    output.at(0).push_back(smaller);
    output.at(0).push_back(remainder);
    output.at(0).push_back(0);

    if (a == 0 || b == 0)
    {
        //
        //Find the linear combination such that ax + by = GCD
        //Push back that linear comb. + GCD
        return output;
    }
    NumTheoryFormulas::SUPERLONG gcd = 0;
    for (int i = 1; (bigger != 0 && smaller != 0); i++)
    {
        NumTheoryFormulas::SUPERLONG t = bigger;
        bigger =  smaller;
        smaller = t - quotient*smaller;

        if (smaller != 0)
        {
            quotient = bigger / smaller;
            remainder = bigger % smaller;
        }

        else
        {
            remainder = 0;
            gcd = bigger;
        }


        output.push_back(std::vector<NumTheoryFormulas::SUPERLONG>());
        output.at(i).push_back(bigger);
        output.at(i).push_back(quotient);
        output.at(i).push_back(smaller);
        output.at(i).push_back(remainder);
        output.at(i).push_back(0);



    }

    //If we get here, either bigger OR smaller = 0, GCD is the greater of the two
    //Find the linear combination such that ax + by = GCD via looping waaaaay back through the matrix somehow, gonna be ugly af
    //Push back that linear comb. + GCD

    //long gcd = (*output.end()).at(0);
    //if (gcd == 0)
    //{
    //	gcd = (*output.end()).at(2);
    //}

    NumTheoryFormulas::SUPERLONG curr[2] = { 1,0 };
    NumTheoryFormulas::SUPERLONG next[2] = { 0,1 };
    NumTheoryFormulas::SUPERLONG temp[2] = { 0,0 };
    for (auto i = output.begin(); i!=output.end(); i++)
    {
        temp[0] = next[0];
        temp[1] = next[1];

        next[0] =   curr[0] - (*i).at(1)*next[0];
        next[1] =  curr[1]- (*i).at(1)*next[1];

        curr[0] = temp[0];
        curr[1] = temp[1];



    }

    output.push_back(std::vector<NumTheoryFormulas::SUPERLONG>());
    output.at(output.size()-1).push_back(std::max(a, b));
    output.at(output.size()-1).push_back(next[0]);
    output.at(output.size()-1).push_back(std::min(a, b));
    output.at(output.size()-1).push_back(next[1]);
    output.at(output.size()-1).push_back(gcd);

//Print output here

    printf("A   Q   B   R   GCD\n");

    for (auto i = output.begin(); i != output.end(); i++)
    {
        if (i != output.end() - 2)
        {
            for (int j = 0; j < 5; j++)
            {
                printf("%li", (*i).at(j));
                printf("%s", "   ");
            }
            printf("\n");
        }
    }

    return output;

}


NumTheoryFormulas::SUPERLONG NumTheoryFormulas::ModExponent(NumTheoryFormulas::SUPERLONG base, NumTheoryFormulas::SUPERLONG exp, NumTheoryFormulas::SUPERLONG mod)
{
    NumTheoryFormulas::SUPERLONG m = 1;
NumTheoryFormulas::SUPERLONG b = base % mod;
    NumTheoryFormulas::SUPERLONG e = exp;

    long long testE, testB, testM;
    testE = e.toLongLong();
    testB = b.toLongLong();
    testM = mod.toLongLong();


    if(mod ==1)// exp ==0)
    {
        return 0;
    }

    else if (exp == 0)
    {
        return 1;
    }
    while(e!=0)
    {

        if (e % 2 == 1)
        {
            //m *= (b%mod);
            m = (m*b)%mod;
            testM = m.toLongLong();
            testB = b.toLongLong();
            testE = e.toLongLong();
            int qqq = 1;

        }

        e = e / 2;
        b =b*b;
        b = b%mod;
        //b = b%mod;
        //b %= mod;
        //b *= (b%mod);
    }
    long long test = m.toLongLong();
    return m;
}

NumTheoryFormulas::SUPERLONG NumTheoryFormulas::MultInverse(NumTheoryFormulas::SUPERLONG a, NumTheoryFormulas::SUPERLONG mod)
{
    NumTheoryFormulas::SUPERLONG xCoef = a%mod;
    long long at = a.toLongLong();
    long long te = xCoef.toLongLong();
    long long modt = mod.toLongLong();
    //long myB= b%mod;
    NumTheoryFormulas::SUPERLONG myMod = mod;
    if (GCD(xCoef, myMod) > 1)
    {
        return exitOnFailure(FAILPAIR(-1, false));
    }




    //Euclidean algorithm, return the coef of b in the final row

    std::vector<std::vector<NumTheoryFormulas::SUPERLONG>> output = std::vector<std::vector<NumTheoryFormulas::SUPERLONG>>();
    //matrix format:  bigger, quotient, smaller, remainder, GCD

    NumTheoryFormulas::SUPERLONG bigger = std::max(xCoef, myMod);
    NumTheoryFormulas::SUPERLONG smaller = std::min(xCoef, myMod);

    NumTheoryFormulas::SUPERLONG quotient = bigger / smaller;
    NumTheoryFormulas::SUPERLONG remainder = bigger % smaller;

    output.push_back(std::vector<NumTheoryFormulas::SUPERLONG>());
    output.at(0).push_back(bigger);
    output.at(0).push_back(quotient);
    output.at(0).push_back(smaller);
    output.at(0).push_back(remainder);
    output.at(0).push_back(0);

    if (mod == 0 || xCoef == 0)
    {
        //
        //Find the linear combination such that ax + by = GCD
        //Push back that linear comb. + GCD
        return exitOnFailure(std::pair<NumTheoryFormulas::SUPERLONG, bool>(-1, false));
    }
    NumTheoryFormulas::SUPERLONG gcd = 0;
    for (int i = 1; (bigger != 0 && smaller != 0); i++)
    {
        NumTheoryFormulas::SUPERLONG t = bigger;
        bigger = smaller;
        smaller = t - quotient*smaller;

        if (smaller != 0)
        {
            quotient = bigger / smaller;
            remainder = bigger % smaller;
        }

        else
        {
            remainder = 0;
            gcd = bigger;
        }


        output.push_back(std::vector<NumTheoryFormulas::SUPERLONG>());
        output.at(i).push_back(bigger);
        output.at(i).push_back(quotient);
        output.at(i).push_back(smaller);
        output.at(i).push_back(remainder);
        output.at(i).push_back(0);



    }

    //If we get here, either bigger OR smaller = 0, GCD is the greater of the two
    //Find the linear combination such that ax + by = GCD via looping waaaaay back through the matrix somehow, gonna be ugly af
    //Push back that linear comb. + GCD

    //long gcd = (*output.end()).at(0);
    //if (gcd == 0)
    //{
    //	gcd = (*output.end()).at(2);
    //}

    NumTheoryFormulas::SUPERLONG curr[2] = { 1,0 };
    NumTheoryFormulas::SUPERLONG next[2] = { 0,1 };
    NumTheoryFormulas::SUPERLONG temp[2] = { 0,0 };
    for (auto i = output.begin(); i != output.end(); i++)
    {
        temp[0] = next[0];
        temp[1] = next[1];
        next[0] = curr[0] - (*i).at(1)*next[0];
        next[1] = curr[1] - (*i).at(1)*next[1];

        curr[0] = temp[0];
        curr[1] = temp[1];



    }

    if (next[1] >= mod)
    {
        next[1] %= mod;
    }





    output.push_back(std::vector<NumTheoryFormulas::SUPERLONG>());
    output.at(output.size() - 1).push_back(std::max(a, mod));
    output.at(output.size() - 1).push_back(next[0]);
    output.at(output.size() - 1).push_back(std::min(a, mod));
    output.at(output.size() - 1).push_back(next[1]);
    output.at(output.size() - 1).push_back(gcd);

    //Print output here

    //printf("A   Q   B   R   GCD\n");

    //for (auto i = output.begin(); i != output.end(); i++)
    //{
    //	if (i != output.end() - 2)
    //	{
    //		for (int j = 0; j < 5; j++)
    //		{
    //			printf("%lli", (*i).at(j));
    //			printf("%s", "   ");
    //		}
    //		printf("\n");
    //	}
    //}


    while (next[1]<0)
    {
        next[1] += mod;
    }
    long long l = next[1].toLongLong();
    return exitOnFailure(std::pair<NumTheoryFormulas::SUPERLONG,bool>(next[1],true));
    /*if (b % gcd == 0)
    {
        return next[1];
    }

    else
    {
        //No solutions
        return -1;
    }
    */


}

NumTheoryFormulas::SUPERLONG NumTheoryFormulas::CRT( int numEqns, NumTheoryFormulas::SUPERLONG eqns[][2])
{
    NumTheoryFormulas::SUPERLONG bigM = eqns[0][1];
    long long bM = bigM.toLongLong();
    long long te = eqns[1][1].toLongLong();
    NumTheoryFormulas::SUPERLONG gcd = this->GCD(bigM, eqns[1][1]);
    bigM = bigM* eqns[1][1];
    for (int i = 2; i < numEqns; i++)
    {
        if (gcd != 1)
        {
            //No solution, abort)
            return exitOnFailure(std::pair<NumTheoryFormulas::SUPERLONG, bool>(-1,false));
        }

        gcd = this->GCD(gcd, eqns[0][i]);
    }




    //NumTheoryFormulas::SUPERLONG* mArray = new NumTheoryFormulas::SUPERLONG(sizeof(NumTheoryFormulas::SUPERLONG) * numEqns);
    //mArray[0] = bigM;
    for (int i = 2; i < numEqns; i++)
    {
        //mArray[i] = eqns[i][1];
        bigM =  bigM* eqns[i][1];

    }
    bM = bigM.toLongLong();
    NumTheoryFormulas::SUPERLONG out = 0;
    NumTheoryFormulas::SUPERLONG mTemp;
    for (int i = 0; i < numEqns; i++)
    {
        mTemp = bigM / eqns[i][1];
        out += ((this->MultInverse(mTemp, eqns[i][1])* eqns[i][0]*mTemp) % bigM);
    }
    out = out % bigM;
    return exitOnFailure(std::pair<NumTheoryFormulas::SUPERLONG,bool>((out % bigM),true));

}

NumTheoryFormulas::SUPERLONG NumTheoryFormulas::GCD(NumTheoryFormulas::SUPERLONG a, NumTheoryFormulas::SUPERLONG b)
{
    NumTheoryFormulas::SUPERLONG a1(a);
    NumTheoryFormulas::SUPERLONG b1(b);

    long long ta = a.toLongLong();
    long long tb = b.toLongLong();

        while (b1 != 0) {
            NumTheoryFormulas::SUPERLONG r = a1 % b1;
            a1 = b1;
            b1 = r;
        }
        long long t = a1.toLongLong();
        return a1;

}


NumTheoryFormulas::SUPERLONG NumTheoryFormulas::decrypt(NumTheoryFormulas::SUPERLONG msg, NumTheoryFormulas::SUPERLONG exp, NumTheoryFormulas::SUPERLONG p, NumTheoryFormulas::SUPERLONG q)
{
    NumTheoryFormulas::SUPERLONG One(1);// = NumTheoryFormulas::SUPERLONG(-1);

    if(GCD((p-1)*(q-1),exp) != 1)
    {
        return exitOnFailure(FAILPAIR(-1, false));
    }

    else
    {
        NumTheoryFormulas::SUPERLONG msgCopy = msg;
        NumTheoryFormulas::SUPERLONG eCopy = exp;
        NumTheoryFormulas::SUPERLONG phiN = (p - 1)*(q - 1);
        long long phi = phiN.toLongLong();
        NumTheoryFormulas::SUPERLONG bigN( p*q);
        long long N = bigN.toLongLong();
        NumTheoryFormulas::SUPERLONG d = MultInverse(eCopy, phiN);
        //std::cout << d << std::endl;
        return exitOnFailure(FAILPAIR(ModExponent(msgCopy, (d), bigN), true));
    }

}

NumTheoryFormulas::SUPERLONG NumTheoryFormulas::decryptionExponent(NumTheoryFormulas::SUPERLONG exp, NumTheoryFormulas::SUPERLONG p, NumTheoryFormulas::SUPERLONG q)
{
    NumTheoryFormulas::SUPERLONG copy = (p-1)*(q-1);
    NumTheoryFormulas::SUPERLONG eCopy = exp;
    return MultInverse(eCopy, copy);
}


NumTheoryFormulas::SUPERLONG NumTheoryFormulas::exitOnFailure(NumTheoryFormulas::FAILPAIR f)
{
    if (f.second)
    {
        return f.first;
    }

    else
    {

        exit(-1);
    }
}

NumTheoryFormulas::SUPERLONG NumTheoryFormulas::order(NumTheoryFormulas::SUPERLONG a, NumTheoryFormulas::SUPERLONG base)
{
    if (GCD(a, base) != 1)
    {
        return exitOnFailure(FAILPAIR(-1, false));
    }

    NumTheoryFormulas::SUPERLONG holder, out;
    for (NumTheoryFormulas::SUPERLONG i = 1; i <= base; i++)
    {
        holder = ModExponent(i, 1, base);
        if (holder == 0 && (out = ModExponent(a,i,base))==0)
        {
            return out;
        }
    }
}


std::vector<NumTheoryFormulas::SUPERLONG> NumTheoryFormulas::factorize(NumTheoryFormulas::SUPERLONG a)
{
    std::vector<SUPERLONG> out;
    SUPERLONG temp;
    for (SUPERLONG i = 1; i <= a; i++)
    {
        temp = ModExponent(i, 1, a);
        if (temp == 0)
        {
            out.push_back(i);
        }
    }

    return out;

}

void NumTheoryFormulas::printFactors(std::vector<NumTheoryFormulas::SUPERLONG> a)
{
    std::ofstream out;
    std::string filename("Factorization");
    //filename += a.toString();
    out.open(filename);
    int k = 0;
    for (auto i = a.begin(); i != a.end(); i++)
    {
        if(k==5)
        {
            k = 0;
            std::cout << std::endl;
            out << std::endl;
        }

        std::cout << i->toString() << "\t";
        out << i->toString() << "\t";
        k++;

    }
    out.close();
}

void NumTheoryFormulas::printFactors(NumTheoryFormulas::SUPERLONG a)
{
    printFactors(factorize(a));
}

NumTheoryFormulas::SUPERLONG NumTheoryFormulas::discreteLogBruteForce(NumTheoryFormulas::SUPERLONG pRoot, NumTheoryFormulas::SUPERLONG val, NumTheoryFormulas::SUPERLONG mod)
{
    SUPERLONG out = -1;
    for (SUPERLONG i = 1; i <= mod; i++)
    {
        if(val==ModExponent(pRoot,i,mod))
        {
            return i;
        }
    }

}


NumTheoryFormulas::SUPERLONG NumTheoryFormulas::discreteLogBabyStepGiantStep(NumTheoryFormulas::SUPERLONG pRoot, NumTheoryFormulas::SUPERLONG val, NumTheoryFormulas::SUPERLONG mod)
{
    std::vector<SUPERLONG> small, big;

    SUPERLONG bigN = (mod - 1).intSqrt();
    SUPERLONG temp, inv;
    for (SUPERLONG i = 1; i <= bigN; i++)
    {
        small.push_back(ModExponent(pRoot, i, mod));
        temp = pRoot;
        for (SUPERLONG j = 1; j < bigN; j++)
        {
            temp *= pRoot;
        }
        temp *= (bigN+1);
        inv = MultInverse(temp, mod);
        inv *= val;


        big.push_back(ModExponent(inv, 1, mod));
        small.push_back(ModExponent(pRoot, i, mod));
    }

    for(SUPERLONG i=0;i<=bigN;i++)
    {
        for (SUPERLONG j = 0; j <= bigN; j++)
        {
            if (big.at(i.toUnsignedLongLong()) == small.at(j.toUnsignedLongLong()))
            {
                return (i + (j*(bigN + 1)));
            }
        }
    }



}

NumTheoryFormulas::NumTheoryFormulas()
{
}


NumTheoryFormulas::~NumTheoryFormulas()
{
}
