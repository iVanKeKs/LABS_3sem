
#include<iostream>
#include<cstring>
#include<algorithm>

#include "LargeInteger.h"

LargeIntegerException::LargeIntegerException()
    :error(nullptr)
{}

LargeIntegerException::LargeIntegerException(const char *errorName)
{
	if (errorName)
	{
		error = new char[strlen(errorName) + 1];
		strcpy(error, errorName);
	}
	else
	{
		error = nullptr;
	}
}

LargeIntegerException::LargeIntegerException(const LargeIntegerException &exception)
{
	if (exception.error)
	{
		error = new char[strlen(exception.error) + 1];
		strcpy(error, exception.error);
	}
	else
	{
		error = nullptr;
	}
}

LargeIntegerException::~LargeIntegerException()
{
	delete[] error;
}

const char *LargeIntegerException::WhatExceptions()
{
	return error;
}


LargeInteger::LargeInteger()
{
	data = nullptr;
	size = 0;
	base = 0;
    isPlus = true;
}

LargeInteger::LargeInteger(const char *inputNumber, int baseOfNewNumber)
{
	if (baseOfNewNumber == 0)
	{
		throw LargeIntegerException("Base of number is 0");
	}

	int lengthOfNewNumber;

	char *buff = nullptr;
	char *pbuff;
	
	if (isdigit(*inputNumber))
	{
        lengthOfNewNumber = strlen(inputNumber);
        isPlus = true;
        buff = new char[lengthOfNewNumber + 1];
		strcpy(buff, inputNumber);
        pbuff = buff + lengthOfNewNumber;
	}
	else
	{
        lengthOfNewNumber = strlen(inputNumber + 1);
		if (*inputNumber == '+')
		{
            isPlus = true;
		}
		else if (*inputNumber == '-')
		{
            isPlus = false;
		}
		else
		{
			throw LargeIntegerException("Invalid sign");
		}
        buff = new char[lengthOfNewNumber + 1];

		strcpy(buff, inputNumber + 1);
        pbuff = buff + lengthOfNewNumber;
	}

	
	int currentNumber = 0;

	base = baseOfNewNumber;
	size = round((double)lengthOfNewNumber/base);
	data = new int[size];

	for (int i = 0; i < size; ++i)
	{
        pbuff -= base;
		if (pbuff < buff)
		{
            pbuff = buff;
		}

        currentNumber = atoi(pbuff);
		*pbuff = 0;
		data[i] = currentNumber;
	}

	delete[] buff;
}

LargeInteger::LargeInteger(int inputNumber)
{
	int buff = inputNumber;
	int countNumerals = 0;

	while (buff != 0)
	{
        buff /= 10;
		++countNumerals;
	}

	if (countNumerals == 0)
	{
		data = new int[1];
		data[0] = 0;
		size = 1;
		base = 1;
        isPlus = true;
	}
	else
	{
		data = new int[countNumerals];
		size = countNumerals;
		base = 1;

		if (inputNumber < 0)
		{
            isPlus = false;
		}
		else
		{
            isPlus = true;
		}

		for (int i = 0; inputNumber; ++i)
		{
			data[i] = inputNumber % 10;
            inputNumber /= 10;
		}
	}
}

LargeInteger::LargeInteger(const LargeInteger &sourceNumber)
{
	if (sourceNumber.size > 0)
	{
		data = new int[sourceNumber.size];
		size = sourceNumber.size;
		base = sourceNumber.base;
        isPlus = sourceNumber.isPlus;

		for (int i = 0; i < size; ++i)
		{
			*(data + i) = *(sourceNumber.data + i);
		}
	}
	else
	{
		data = nullptr;
		size = 0;
		base = 0;
        isPlus = true;
	}
}

LargeInteger::LargeInteger(const LargeInteger &sourceNumber, bool plus)
{
	if (sourceNumber.size > 0)
	{
		data = new int[sourceNumber.size];
		size = sourceNumber.size;
		base = sourceNumber.base;
        isPlus = plus;

		for (int i = 0; i < size; ++i)
		{
			data[i] = sourceNumber.data[i];
		}
	}
	else
	{
		data = nullptr;
		size = 0;
		base = 0;
        isPlus = plus;
	}
}

LargeInteger::LargeInteger(const LargeInteger &sourceNumber, int startIndex, int endIndex)
{
    if(startIndex > endIndex || sourceNumber.size == 0)
    {
        data = nullptr;
        size = 0;
        base = 0;
        isPlus = true;
    }
    else
    {
        if (startIndex < 0)
        {
            startIndex = 0;
        }

        if (startIndex > sourceNumber.size - 1)
        {
            startIndex = sourceNumber.size - 1;
        }

        if (endIndex < 0)
        {
            endIndex = 0;
        }

        if (endIndex > sourceNumber.size)
        {
            endIndex = sourceNumber.size;
        }

        int newSize = endIndex - startIndex;
        data = new int[newSize];
        size = newSize;
        base = sourceNumber.base;
        isPlus = true;

        newSize = 0;

        for (int i = startIndex; i < endIndex; ++i, ++newSize)
        {
            data[newSize] = sourceNumber.data[i];
        }
    }
}

LargeInteger::LargeInteger(LargeInteger &&sourceNumber)
{
	data = sourceNumber.data;
    size = sourceNumber.size;
    base = sourceNumber.base;
    isPlus = sourceNumber.isPlus;

    sourceNumber.data = nullptr;
    sourceNumber.size = 0;
    sourceNumber.base = 0;
    sourceNumber.isPlus = true;
}


LargeInteger::~LargeInteger()
{
	delete[] data;
}


LargeInteger& LargeInteger::operator =(const LargeInteger &rightNumber)
{
	if (&rightNumber == this)
	{
		return *this;
	}

    delete[] data;

	size = rightNumber.size;
	base = rightNumber.base;
    isPlus = rightNumber.isPlus;

	data = new int[size];

	for (int i = 0; i < size; ++i)
	{
	    data[i] = rightNumber.data[i];
	}

	return *this;
}

LargeInteger& LargeInteger::operator =(LargeInteger &&rightNumber)
{
	if (&rightNumber == this)
	{
		return *this;
	}

    delete[] data;

	data = rightNumber.data;
    size = rightNumber.size;
    base = rightNumber.base;
    isPlus = rightNumber.isPlus;

    rightNumber.data = nullptr;
    rightNumber.size = 0;
    rightNumber.base = 0;
    rightNumber.isPlus = true;

	return *this;
}


LargeInteger& LargeInteger::operator +=(const LargeInteger &rightNumber)
{
	if (rightNumber.size == 0)
    {
	    return *this;
    }

	if (rightNumber.base != base)
    {
	    throw LargeIntegerException("Not same bases");
    }

	LargeInteger rightBuff(rightNumber, true);

	if (isPlus == true && rightNumber.isPlus == false)
	{
		return (*this) -= rightBuff;
	}

	if (isPlus == false && rightNumber.isPlus == true)
	{
        isPlus = true;
		Swap(rightBuff);
		return (*this) -= rightBuff;
	}

	if (size <= rightBuff.size)
    {
        AddNewNumeralInStart(rightBuff.size + 1);
    }

	int minSizeOfTwo = std::min(size, rightBuff.size);
	
	int remainder = 0,
	    buff;

	int baseBuff = pow(10, base);

	int i;
	for (i = 0; i < minSizeOfTwo; ++i)
	{
        buff = data[i] + rightBuff.data[i] + remainder;
        remainder = buff / baseBuff;
		data[i] = buff % baseBuff;
	}

	if (remainder != 0)
	{
		data[i] += remainder;
	}

    NumberNormalization();

	return *this;
}

LargeInteger &LargeInteger::operator -=(const LargeInteger &rightNumber)
{
    if (rightNumber.size == 0)
    {
        return *this;
    }

	if (rightNumber.base != base)
    {
	    throw LargeIntegerException("Not same bases");
    }

	{
		LargeInteger rightBuff(rightNumber);
		if ((*this) == rightBuff)
		{
			(*this) = LargeInteger("0", base);
			return *this;
		}
	}

	LargeInteger rightBuff(rightNumber, true);

	if (isPlus == true && rightNumber.isPlus == false)
	{
	    return (*this) += rightBuff;
	}

	if (isPlus == false && rightNumber.isPlus == true)
	{
        isPlus = true;
        (*this) += rightBuff;
        isPlus = false;
		return *this;
	}

	if (isPlus == false && rightNumber.isPlus == false)
	{
        isPlus = true;
		if ((*this) < rightBuff)
		{
			Swap(rightBuff);
		}
		else
		{
            isPlus = false;
		}
	}

	if (isPlus == true && rightNumber.isPlus == true && (*this) < rightBuff)
	{
		Swap(rightBuff);
        isPlus = false;
	}

	if (size <= rightBuff.size)
    {
	    AddNewNumeralInStart(rightBuff.size + 1);
    }

	int minSizeOfTwo = std::min(size, rightBuff.size);

	int remainder = 0,
	    buff;

	int baseBuff = pow(10, base);

	int i;
	for (i = 0; i < minSizeOfTwo; ++i)
	{
        buff = data[i] - rightBuff.data[i] + remainder;
		if (buff >= 0)
		{
			data[i] = buff;
            remainder = 0;
		}
		else
		{
            buff += baseBuff;
            remainder = -1;
			data[i] = buff;
		}
	}

	if (remainder != 0)
	{
        buff = data[i] + remainder;
		if (buff >= 0)
		{
			data[i] = buff;
		}
		else
		{
            buff += baseBuff;
			data[i] = buff;
		}
	}

    NumberNormalization();

	return *this;
}

LargeInteger& LargeInteger::operator *=(const LargeInteger &rightNumber)
{
	bool buffPlus = isPlus;
    isPlus = true;
	bool buffPlusRight = rightNumber.isPlus;

	(*this) = KaratsubaMultiple(rightNumber);

	if ((buffPlus == true && buffPlusRight == false) || (buffPlus == false && buffPlusRight == true))
	{
        isPlus = false;
	}

	return *this;
}

LargeInteger& LargeInteger::operator *=(int rightNumber)
{
    AddNewNumeralInStart(size + 1);

	int baseBuff = pow(10, base);

	int i,
	    remainder = 0,
	    buff;

	for (i = 0; i < size; ++i)
	{
        buff = data[i] * rightNumber + remainder;
		if (buff >= base)
		{
            remainder = buff / baseBuff;
		}
		else
		{
            remainder = 0;
		}

		data[i] = buff % baseBuff;
	}

	if (remainder != 0)
	{
		data[i] += remainder;
	}

    NumberNormalization();
	return *this;
}

LargeInteger LargeInteger::MulInt(int x)
{
	LargeInteger res(*this);

    res.AddNewNumeralInStart(size + 3);

	int base_ = (int)pow(10, res.base);

	int i, carry = 0, tmp;
	for (i = 0; i < res.size; ++i)
	{
		tmp = res.data[i] * x + carry;
		if (tmp >= base_)
		{
			carry = tmp / base_;
		}
		else
		{
			carry = 0;
		}
		res.data[i] = tmp % base_;
	}

	if (carry)
	{
		res.data[i] += carry;
	}

    res.NumberNormalization();
	return res;
}

LargeInteger& LargeInteger::operator /=(const LargeInteger &rightNumber)
{
	if (rightNumber.size == 0)
	{
		throw LargeIntegerException("Division by zero");
	}

	if (rightNumber.base != base)
    {
	    throw LargeIntegerException("Not same bases");
    }

	bool plusBuff = isPlus;
    isPlus = true;
	bool plusBuffRight = rightNumber.isPlus;

	LargeInteger buffNumberRight(rightNumber, true);

    NumberNormalization();
    buffNumberRight.NumberNormalization();

	if (size < buffNumberRight.size)
	{
		(*this) = LargeInteger("0", base);

		return *this;
	}

	if (buffNumberRight.size == 0 && buffNumberRight.data[0] == 0)
	{
		throw LargeIntegerException("Division by zero");
	}

	LargeInteger resultNumber;

	int zeroNumerals = size - buffNumberRight.size;
    resultNumber.base = base;

	while((*this) > (buffNumberRight))
	{
		LargeInteger minusNumber(buffNumberRight);
        minusNumber.AddNewNumeralInEnd(minusNumber.size + zeroNumerals);

		int index = 0;
		while ((*this) >= (minusNumber))
		{
            (*this) -= minusNumber;
			++index;
		}

        resultNumber.AddNewNumeralInEnd(resultNumber.size + 1);
        resultNumber.data[0] = index;
		--zeroNumerals;
	}

	if (zeroNumerals != -1)
	{
        resultNumber.AddNewNumeralInEnd(resultNumber.size + zeroNumerals + 1);
	}

    (*this) = resultNumber;
    NumberNormalization();

	if ((plusBuff == true && plusBuffRight == false) || (plusBuff == false && plusBuffRight == true))
	{
        isPlus = false;
	}

	return *this;
}

LargeInteger& LargeInteger::operator %=(const LargeInteger &rightNumber)
{
	if (rightNumber.size == 0)
	{
		throw LargeIntegerException("Division by zero");
	}

	if (rightNumber.base != base)
    {
	    throw LargeIntegerException("Not same bases");
    }

	LargeInteger buffNumberRight(rightNumber);

    NumberNormalization();
    buffNumberRight.NumberNormalization();

	if (size < buffNumberRight.size)
	{
		(*this) = LargeInteger("0", base);

		return *this;
	}

	if (buffNumberRight.size == 0 && buffNumberRight.data[0] == 0)
	{
		throw LargeIntegerException("Division by zero");
	}

	int zeroNumerals = size - buffNumberRight.size;

	while ((*this) > buffNumberRight)
	{
		LargeInteger minuNumber(buffNumberRight);
        minuNumber.AddNewNumeralInEnd(minuNumber.size + zeroNumerals);

		while ((*this) > minuNumber)
		{
            (*this) -= minuNumber;
		}
		--zeroNumerals;
	}

	return *this;
}

bool LargeInteger::operator <(LargeInteger &rightNumber)
{
    NumberNormalization();
    rightNumber.NumberNormalization();

    if (size == 0 && rightNumber.size == 0)
    {
        return false;
    }

    if (size == 1 && rightNumber.size == 1 && data[0] == 0 && rightNumber.data[0] == 0)
	{
		return false;
	}

	if (isPlus == true)
	{
		if (rightNumber.isPlus == false)
        {
		    return false;
        }

		if (size > rightNumber.size)
        {
		    return false;
        }

		if (size < rightNumber.size)
        {
		    return true;
        }

		for (int i = rightNumber.size - 1; i >= 0; --i)
		{
            if(data[i] < rightNumber.data[i])
            {
                return true;
            }
		    if(data[i] > rightNumber.data[i])
            {
                return false;
            }
		}

		return false;
	}

	if (isPlus == false)
	{
		if (rightNumber.isPlus == true)
        {
		    return true;
        }

		if (size > rightNumber.size)
        {
		    return true;
        }

		if (size < rightNumber.size)
        {
		    return false;
        }

		for (int i = rightNumber.size - 1; i >= 0; --i)
		{
            if (data[i] > rightNumber.data[i])
            {
                return true;
            }

			if (data[i] < rightNumber.data[i])
            {
			    return false;
            }
		}

		return false;
	}
}

bool LargeInteger::operator ==(LargeInteger &rightNumber)
{
    NumberNormalization();
    rightNumber.NumberNormalization();

	if (size != rightNumber.size)
	{
		return false;
	}

	if (isPlus != rightNumber.isPlus)
	{
		return false;
	}

	for (int i = 0; i < size; ++i)
	{
		if (data[i] != rightNumber.data[i])
        {
		    return false;
        }
	}

	return true;
}

bool LargeInteger::operator >(LargeInteger &rightNumber)
{
    return !((*this) < rightNumber) && !((*this) == rightNumber);
}

bool LargeInteger::operator >=(LargeInteger &rightNumber)
{
    return (*this) > rightNumber || (*this) == rightNumber;
}


std::ostream& operator <<(std::ostream &outputStream, const LargeInteger &outputNumber)
{
	if (outputNumber.size && !outputNumber.isPlus)
	{
		outputStream << "-";
	}

	for (int i = outputNumber.size - 1; i >= 0; --i)
	{
		outputStream << outputNumber.data[i];
	}

	return outputStream;
}

std::istream& operator >>(std::istream &inputStream, LargeInteger &inputNumber)
{
	char buff[BUFSIZ];
	int base;

	inputStream >> base;
	inputStream >> buff;

    inputNumber = LargeInteger(buff, base);

	return inputStream;
}



LargeInteger operator +(const LargeInteger &leftNumber, const LargeInteger &rightNumber)
{
	LargeInteger newNumber(leftNumber);
    newNumber += rightNumber;
	return newNumber;
}

LargeInteger operator -(const LargeInteger &leftNumber, const LargeInteger &rightNumber)
{
	LargeInteger newNumber(leftNumber);
    newNumber -= rightNumber;
	return newNumber;
}

LargeInteger operator *(const LargeInteger &leftNumber, const LargeInteger &rightNumber)
{
	LargeInteger newNumber(leftNumber);
    newNumber *= rightNumber;
	return newNumber;
}

LargeInteger operator /(const LargeInteger &leftNumber, const LargeInteger &rightNumber)
{
	LargeInteger newNumber(leftNumber);
    newNumber /= rightNumber;
	return newNumber;
}

LargeInteger operator %(const LargeInteger &leftNumber, const LargeInteger &rightNumber)
{
	LargeInteger newNumber(leftNumber);
    newNumber %= rightNumber;
	return newNumber;
}

void LargeInteger::AddNodesWhileNotEven()
{
    if (size == 2 && data[1] == 0)
    {
        size = 1;
        int dataBuff = data[0];

        delete[] data;

        data = new int[size];
        data[0] = dataBuff;

        return;
    }

    if (size & 1)
    {
        if (data[size - 1] == 0)
        {
            int *dataBuff = data;
            data = new int[size--];

            for (int i = 0; i < size; ++i)
            {
                data[i] = dataBuff[i];
            }

            delete[] dataBuff;
            return;
        }

        int *dataBuff = data;
        data = new int[size + 1];

        for (int i = 0; i < size + 1; ++i)
        {
            if (i < size)
            {
                data[i] = dataBuff[i];
            }
            else
            {
                data[i] = 0;
            }
        }

        ++size;
        delete[] dataBuff;
    }
}

void LargeInteger::AddNewNumeralInStart(int newSize)
{
	int *dataBuff = data;
	data = new int[newSize];

	for (int i = 0; i < newSize; ++i)
	{
		if (i < size)
        {
		    data[i] = dataBuff[i];
        }
		else
        {
		    data[i] = 0;
        }
	}
	size = newSize;
}

void LargeInteger::AddNewNumeralInEnd(int newSize)
{
	int countZero = newSize - size;

	if (countZero > 0)
	{
		int *dataBuff = data;
		data = new int[newSize];

		int i;
		for (i = 0; i < countZero; ++i)
		{
			data[i] = 0;
		}

		for (; i < newSize; ++i)
		{
			data[i] = dataBuff[i - countZero];
		}

		size = newSize;
	}
}


void LargeInteger::NumberNormalization()
{
	if (size > 1)
	{
		for (int i = size - 1; i > 0; --i)
		{
			if (data[i] != 0)
            {
			    break;
            }
			else
            {
			    --size;
            }
		}

        AddNewNumeralInStart(size);
	}
}

void LargeInteger::Swap(LargeInteger &rightNumber)
{
	std::swap(data, rightNumber.data);
	std::swap(size, rightNumber.size);
	std::swap(base, rightNumber.base);
	std::swap(isPlus, rightNumber.isPlus);
}

LargeInteger LargeInteger::KaratsubaMultiple(const LargeInteger &inputNumber) const
{
	if (inputNumber.size == 0)
    {
	    return LargeInteger(0);
    }

	if (inputNumber.base != base)
    {
	    throw LargeIntegerException("Not same bases");
    }

	if (size == 1 && inputNumber.size == 1)
	{
		return MultSimpleLargeInteger(inputNumber);
	}

	LargeInteger resultNumber;

	LargeInteger X(*this, true);
	LargeInteger Y(inputNumber, true);

	X.NumberNormalization();
	Y.NumberNormalization();

	X.AddNodesWhileNotEven();
	Y.AddNodesWhileNotEven();

	if (X.size == 1 && Y.size == 1)
	{
		return X.MultSimpleLargeInteger(Y);
	}

	const int n = std::max(X.size, Y.size);

	X.AddNewNumeralInStart(n);
	Y.AddNewNumeralInStart(n);

	int k = n / 2;

	LargeInteger Xr(X, 0, k);
	LargeInteger Xl(X, k, INT_MAX);
	LargeInteger Yr(Y, 0, k);
	LargeInteger Yl(Y, k, INT_MAX);

	LargeInteger P1 = Xl.KaratsubaMultiple(Yl);
	LargeInteger P2 = Xr.KaratsubaMultiple(Yr);
	LargeInteger P3 = (Xr + Xl).KaratsubaMultiple(Yl + Yr);
	P1.NumberNormalization();
	P2.NumberNormalization();
	P3.NumberNormalization();

	P3 -= P2;
	P3 -= P1;

	P1.AddNewNumeralInEnd(P1.size + n);
	P3.AddNewNumeralInEnd(P3.size + k);

    resultNumber = P1 + P2 + P3;

	return resultNumber;
}


LargeInteger LargeInteger::MultSimpleLargeInteger(const LargeInteger &inputNumber) const
{
	if (inputNumber.size != 1 || size != 1)
    {
	    throw LargeIntegerException("Size error in MultSimpleLargeInteger");
    }

	if (inputNumber.base != base)
    {
	    throw LargeIntegerException("Not same bases");
    }

	LargeInteger resultNumber;

    resultNumber.size = 2;
    resultNumber.data = new int[resultNumber.size];
    resultNumber.base = base;
    resultNumber.isPlus = true;

    resultNumber.data[0] = 0;
    resultNumber.data[1] = 0;

	int base_ = (int)pow(10, base);

	int tmp = data[0] * inputNumber.data[0];

	if (tmp > base)
	{
        resultNumber.data[1] = tmp / base_;
	}

    resultNumber.data[0] = tmp % base_;

    resultNumber.NumberNormalization();

	return resultNumber;
}


LargeInteger LargeInteger::Pow(int power)
{
	if (power < 0)
	{
		throw LargeIntegerException("Power < 0");
	}

	if (size == 0)
	{
		throw LargeIntegerException("Empty number in Pow");
	}

	LargeInteger resultNumber("1", base);

	while(power != 0)
	{
		if(power & 1)
		{
            resultNumber *= (*this);
		}

        (*this) *= (*this);
        power = power >> 1;
	}

	return resultNumber;
}



LargeInteger LargeInteger::TranslateNumberToBase10()
{
	if (base == 1)
	{
		return LargeInteger(*this);
	}
	
	int baseBuff = pow(10, base);

	LargeInteger resultNumber("0", 1);

	for (int i = 0; i < size; ++i)
	{
        resultNumber += data[i] * (int)pow(baseBuff, i);
	}

	return resultNumber;
}

LargeInteger LargeInteger::TranslateNumberToBaseK(int newBase)
{
	int baseBuff = pow(10, base);

	if (newBase == baseBuff)
	{
		return LargeInteger(*this);
	}

	LargeInteger resultNumber = TranslateNumberToBase10();

	int sizeOfItem = 0;
	while(newBase > 1)
	{
		++sizeOfItem;
        newBase /= 10;
	}

	int countOfItems = round((double)resultNumber.size / sizeOfItem);
	int *buffData = new int[countOfItems];
	int buffIndex = 0;

	for (int i = 0; i < resultNumber.size;)
	{
		int currentNumeral = 0;
		for (int j = 0; j < sizeOfItem && i < resultNumber.size; ++j, ++i)
		{
            currentNumeral += resultNumber.data[i] * (int)pow(10, j);
		}
        buffData[buffIndex] = currentNumeral;
		++buffIndex;
	}

	delete[] resultNumber.data;

    resultNumber.data = buffData;
    resultNumber.size = countOfItems;
    resultNumber.base = sizeOfItem;

	return resultNumber;
}

LargeInteger Factorial(int number)
{
	LargeInteger resultNumber("1", 1);

	while(number != 0)
	{
        resultNumber *= LargeInteger(number);
		number--;
	}

	return resultNumber;
}

LargeInteger BinomialCoefficient(int n, int k)
{
	LargeInteger Cn = ("1", 1);

	while (k != 0)
	{
		Cn = Cn.MulInt(n - k + 1);
		Cn /= k;
		--k;
	}

	return Cn;
}

LargeInteger Fibonacci(int numberOfFibonacciNumbers)
{
	if (numberOfFibonacciNumbers == 0)
	{
		return LargeInteger("0", 1);
	}

	if (numberOfFibonacciNumbers == 1)
	{
		return LargeInteger("1", 1);
	}

	LargeInteger number1("0", 1);
	LargeInteger number2("1", 1);
	LargeInteger number3("1", 1);

	for (int i = numberOfFibonacciNumbers - 2; i > 0; --i)
	{
        number1 = number2;
        number2 = number3;
        number3 = number1 + number2;
	}
	
	return number3;
}
