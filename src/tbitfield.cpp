// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#include "tbitfield.h"




TBitField::TBitField(int length)
{
	if (length <= 0)
		throw exception("incorrect length");
	else
	{
		LengthBit = length;
		LengthMem = LengthBit / (sizeof(TELEM) * 8) + (LengthBit % (sizeof(TELEM) * 8) != 0);
		pMem = new TELEM[LengthMem];
		memset(pMem, 0, LengthMem * sizeof(TELEM));
	}
}




// Конструктор копирования
TBitField::TBitField(const TBitField& bf) 
{
	LengthBit = bf.LengthBit;
	LengthMem = bf.LengthMem;
	pMem = new TELEM[LengthMem];
	for (int i = 0; i < LengthMem; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}


// Индекс Мем для бита n
int TBitField::GetMemIndex(const int n) const 
{
	return n / (sizeof(TELEM) * 8);
}



// Битовая маска для бита n
TELEM TBitField::GetMemMask(const int n) const 
{
	return 1 << (n % (sizeof(TELEM) * 8));
}


// Доступ к битам битового поля
int TBitField::GetLength(void) const // Получить длину  битов
{
	return LengthBit;
}



// Установить бит
void TBitField::SetBit(const int n) 
{
	if (n < LengthBit && n >= 0)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else
		throw exception("incorrect index");
}




// Очистить бит
void TBitField::ClrBit(const int n) 
{
	if (n < LengthBit && n >= 0)
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else
		throw exception("incorrect index");
}


// Получить значение бита
int TBitField::GetBit(const int n) const 
{
	if (n < LengthBit && n >= 0)
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	throw exception("incorrect index");
}





// Битовые операции
TBitField& TBitField::operator=(const TBitField& bf) //Операция  присваивания
{
	if (this != &bf)
	{
		if (pMem != nullptr)
			delete[] pMem;
		LengthBit = bf.LengthBit;
		LengthMem = bf.LengthMem;
		pMem = new TELEM[LengthMem];
		for (int i = 0; i < LengthMem; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}


//Операция сравнения
int TBitField::operator==(const TBitField& bf) const 
{
	if (LengthBit != bf.LengthBit)
		return 0;
	for (int i = 0; i < LengthMem; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;
	return 1;

}


//Операция сравнения
int TBitField::operator!=(const TBitField& bf) const 
{
	return !(*this == bf);
}





// Операция "или"
TBitField TBitField::operator|(const TBitField& bf) 
{
	if (LengthBit > bf.LengthBit)
	{
		TBitField tmp(*this);
		for (int i = 0; i < bf.LengthMem; i++)
			tmp.pMem[i] |= bf.pMem[i];
		return tmp;
	}
	else
	{
		TBitField tmp(bf);
		for (int i = 0; i < LengthMem; i++)
			tmp.pMem[i] |= pMem[i];
		return tmp;
	}
}




// Операция "и"
TBitField TBitField::operator&(const TBitField& bf) 
{
	if (LengthBit > bf.LengthBit)
	{
		TBitField tmp(*this);
		for (int i = 0; i < bf.LengthMem; i++)
			tmp.pMem[i] &= bf.pMem[i];
		for (int i = LengthBit; i < LengthMem * 8; i++)
			tmp.pMem[GetMemIndex(i)] &= ~GetMemMask(i);  
		return tmp;
	}
	else
	{
		TBitField tmp(bf);
		for (int i = 0; i < LengthMem; i++)
			tmp.pMem[i] &= pMem[i];

		for (int i = bf.LengthBit; i < bf.LengthMem * 8; i++)
			tmp.pMem[GetMemIndex(i)] &= ~GetMemMask(i);  

		return tmp;
	}
}





// Операция отрицания
TBitField TBitField::operator~(void) 
{
	TBitField tmp(*this);
	for (int i = 0; i < LengthBit; i++)
	{
		if (tmp.GetBit(i))
			tmp.ClrBit(i);
		else
			tmp.SetBit(i);
	}
	return tmp;
}




//Ввод значений
istream& operator>>(istream& istr, TBitField& bf) 
{
	char inp;
	for (int i = 0; i < bf.LengthMem; i++)
	{
		istr >> inp;
		if (inp == '0')
			bf.ClrBit(i);
		else if (inp == '1')
			bf.SetBit(i);
		else
			throw exception("bad input");
	}
	return istr;
}




// Вывод значений
ostream& operator<<(ostream& ostr, const TBitField& bf) 
	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i))
			ostr << '1';
		else
			ostr << '0';
	return ostr;
}


