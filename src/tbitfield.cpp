// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#include "tbitfield.h"

TBitField::TBitField(int length)
{
	if (length <= 0) throw exception("Length < 0");
	LengthBIT = length;
	if (LengthBIT % sizeof(TELEM) != 0) MLength = LengthBIT / sizeof(TELEM) + 1;
	else MLength = LengthBIT / sizeof(TELEM);
	pMem = new TELEM[MLength];
	memset(pMem, 0, sizeof(TELEM) * MLength);
}



// Конструктор копирования
TBitField::TBitField(const TBitField& bf) 
{
	LengthBIT = bf.LengthBIT;
	MLength = bf.MLength;
	pMem = new TELEM[MLength];
	memcpy(pMem, bf.pMem, MLength * sizeof(TELEM));
}
TBitField::~TBitField()
{
	delete[]pMem;
}






// Индекс для бита 
int TBitField::GetMemIndex(const int number) const 
{
	return number / (sizeof(TELEM) * 8);
}
TELEM TBitField::GetMemMask(const int number) const
{
	return 1 << (number & (sizeof(TELEM) * 8 - 1));
}




// Получить длину т.е число битов
int TBitField::GetLength(void) const 
{
	return LengthBIT;
}




// Установить бит
void TBitField::SetBit(const int number)
{
	if (number >= 0 && number < LengthBIT)
		pMem[GetMemIndex(number)] |= GetMemMask(number);
	else
		throw exception("Going out of range");
}




// Очистить бит
void TBitField::ClrBit(const int number)
{
	if (number < 0 || number > LengthBIT) throw exception("Going out of range");
	pMem[GetMemIndex(number)] &= ~GetMemMask(number);
}




// Получить значение бита
int TBitField::GetBit(const int number) const
{
	if (number >= 0 && number < LengthBIT)
		return pMem[GetMemIndex(number)] & GetMemMask(number);
	else
		throw exception("Error in range ");
}




// Присваивание
TBitField& TBitField::operator=(const TBitField& bf) 
{
	LengthBIT = bf.LengthBIT;
	if (MLength != bf.MLength)
	{
		MLength = bf.MLength;
		delete[]pMem;
		pMem = new TELEM[MLength];
	}
	memcpy(pMem, bf.pMem, MLength * sizeof(TELEM));
	return *this;
}



// Сравнение
int TBitField::operator==(const TBitField& bf) const 
{
	if (LengthBIT != bf.LengthBIT)
		return 0;

	for (size_t i = 0; i < MLength; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return 0;
	}
	return 1;
}
int TBitField::operator!=(const TBitField& bf) const 
{
	return !(*this == bf);
}



TBitField TBitField::operator|(const TBitField& bf) 
{        

	if (LengthBIT > bf.LengthBIT)
	{
		TBitField tmp(*this);
		for (size_t i = 0; i < bf.MLength; i++)
		{
			tmp.pMem[i] |= bf.pMem[i];
		}
		return tmp;
	}
	else
	{
		TBitField tmp(bf);
		for (size_t i = 0; i < MLength; i++)
		{
			tmp.pMem[i] |= pMem[i];
		}
		return tmp;
	}
}



TBitField TBitField::operator&(const TBitField& bf) 
{
	if (LengthBIT >= bf.LengthBIT)
	{
		TBitField tmp(*this);
		for (size_t i = 0; i < bf.MLength; i++)
		{
			tmp.pMem[i] &= bf.pMem[i];
		}
		return tmp;
	}
	else
	{
		TBitField tmp(bf);
		for (size_t i = 0; i < MLength; i++)
		{
			tmp.pMem[i] &= pMem[i];
		}
		return tmp;
	}
}





// Отрицание
TBitField TBitField::operator~(void) 
{
	TBitField tmp(*this);
	for (size_t i = 0; i < LengthBIT; i++) {
		if (GetBit(i))
		{
			tmp.ClrBit(i);
		}
		else
		{
			tmp.SetBit(i);
		}
	}
	return tmp;
}


// Ввод
istream& operator>>(istream& istr, TBitField& bf) 
{
	TELEM in;
	for (size_t i = 0; i < bf.GetLength(); i++)
	{
		istr >> in;
		bf.SetBit(i);
	}
	return istr;
}



// Вывод
ostream& operator<<(ostream& ostr, const TBitField& bf) 
{
	size_t length = bf.GetLength();
	for (size_t i = 0; i < length; i++)
	{
		if (bf.GetBit(i))
			ostr << '1';
		else
			ostr << '0';
	}
	return ostr;
}}
