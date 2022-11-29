// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Битовое поле
#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0)
		throw exception("incorrect length");
	else
	{
		BitLen = len;
		MemLen = BitLen / (sizeof(TELEM) * 8) + (BitLen % (sizeof(TELEM) * 8) != 0);
		pMem = new TELEM[MemLen];
		memset(pMem, 0, MemLen * sizeof(TELEM));
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < BitLen && n >= 0)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else
		throw exception("incorrect index");
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < BitLen && n >= 0)
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else
		throw exception("incorrect index");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < BitLen && n >= 0)
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	throw exception("incorrect index");
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this != &bf)
	{
		if (pMem != nullptr)
			delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;
	return 1;

}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	if (BitLen > bf.BitLen)
	{
		TBitField tmp(*this);
		for (int i = 0; i < bf.MemLen; i++)
			tmp.pMem[i] |= bf.pMem[i];
		return tmp;
	}
	else
	{
		TBitField tmp(bf);
		for (int i = 0; i < MemLen; i++)
			tmp.pMem[i] |= pMem[i];
		return tmp;
	}
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	if (BitLen > bf.BitLen)
	{
		TBitField tmp(*this);
		for (int i = 0; i < bf.MemLen; i++)
			tmp.pMem[i] &= bf.pMem[i];
		for (int i = BitLen; i < MemLen * 8; i++)        // обнуление хвооста
			tmp.pMem[GetMemIndex(i)] &= ~GetMemMask(i);  // ClrBit() не получится использовать т.к. инндекс больше чем BitLen
		return tmp;
	}
	else
	{
		TBitField tmp(bf);
		for (int i = 0; i < MemLen; i++)
			tmp.pMem[i] &= pMem[i];

		for (int i = bf.BitLen; i < bf.MemLen * 8; i++)  // обнуление хвооста
			tmp.pMem[GetMemIndex(i)] &= ~GetMemMask(i);  // ClrBit() не получится использовать т.к. инндекс больше чем BitLen

		return tmp;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(*this);
	for (int i = 0; i < BitLen; i++)
	{
		if (tmp.GetBit(i))
			tmp.ClrBit(i);
		else
			tmp.SetBit(i);
	}
	return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	char inp;
	for (int i = 0; i < bf.MemLen; i++)
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

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i))
			ostr << '1';
		else
			ostr << '0';
	return ostr;
}

