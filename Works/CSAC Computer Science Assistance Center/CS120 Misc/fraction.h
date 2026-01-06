/*
fraction fraction::operator+(fraction frac)
{
    fraction answer;
    answer.num = num + frac.num;
    answer.den = den + frac.den;
    return answer;
}
fraction fraction::operator+(int number)
{
    fraction answer;

    answer.num = num + (number * den);
    answer.den = den;

    return answer;
}
int fraction::operator+(fraction frac)
{
    int answer;
    int resolve = frac.num / frac.den;
    
    answer = this + resolve;

    return answer;
}

fraction x = 3/4
3/4 + 3/5;
3/4 + 1;
1 + 3/4;

fraction f1 = f2 + f3;

fraction sub
f
f

fraction mult
f
f

fraction div
f
f
*/
