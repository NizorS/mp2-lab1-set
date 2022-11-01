// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля
#include "tset.h"



// Множество - реализация через битовые поля
TSet::TSet(int mp) : BitField(mp)
{
    PowMaxi = mp;
}



// Конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    PowMaxi = s.PowMaxi;
}





// Конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    PowMaxi = bf.GetLength();
}
TSet::operator TBitField()
{
    return BitField;
}





// Получить максммальное количество элементов
int TSet::GetMaxPower(void) const 
{
    return PowMaxi;
}


// Элемент множества
int TSet::IsMember(const int Element) const 
{
    if (BitField.GetBit(Element))
        return 1;
    else
        return 0;
}


// Включение элемента множества
void TSet::InsElem(const int Element) 
{
    BitField.SetBit(Element);
}
// Исключение элемента множества
void TSet::DelElem(const int Element) 
{
    BitField.ClrBit(Element);

}



// Присваивание
TSet& TSet::operator=(const TSet& s) 
{
    PowMaxi = s.PowMaxi;
    BitField = s.BitField;
    return *this;
}


// Сравнение
int TSet::operator==(const TSet& s) const 
{
    return BitField == s.BitField;
}
int TSet::operator!=(const TSet& s) const 
{
    return BitField != s.BitField;
}


// Объединение
TSet TSet::operator+(const TSet& s) 
{
    TSet adding(max(PowMaxi, s.PowMaxi));
    adding.BitField = BitField | s.BitField;
    return adding;
}
TSet TSet::operator+(const int Element) 
    TSet adding(*this);
    adding.BitField.SetBit(Element);
    return adding;
}


// Разность 
TSet TSet::operator-(const int Element) 
{
    TSet difference(*this);
    difference.BitField.ClrBit(Element);
    return difference;
}


// Пересечение
TSet TSet::operator*(const TSet& s) 
{
    TSet intersection(max(PowMaxi, s.PowMaxi));
    intersection.BitField = BitField & s.BitField;
    return intersection;
}


// Дополнение
TSet TSet::operator~(void) 
{
    TSet addition(PowMaxi);
    addition.BitField = ~BitField;
    return addition;
}






// Ввод
istream& operator>>(istream& istr, TSet& s) 
{
    istr >> s.BitField;
    return istr;
}


// Вывод
ostream& operator<<(ostream& ostr, const TSet& s) 
{
    ostr << s.BitField;
    return ostr;
}
