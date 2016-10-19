// John Lahut

//  Lab #11 - asm overflow

#include <iostream>
using namespace std;
void main()
{
	//Making luke proud
	const int FIVE = 5;
	const int THREE = 3;
	const int THIRTY = 30;
	const int FOURTEEN = 14;
	const int SEVEN = 7;
	const int FIFTY_THREE = 53;


	int num1, num2, result;

	num1 = 1000000000;
	num2 = 2000000000;

	//****PART A*****

	cout << "Part A:" << endl;
	cout << "Without inline assembly: " << 5 * num2 / 5 << endl;
	__asm
	{
		;cant use immediates w/ div&mul?
	
		mov eax, num2		;eax = num 2
		imul FIVE			;edx:eax = 5*eax
		idiv FIVE			;eax = edx:eax / 5
		mov result, eax		;result = eax

	}

	cout << "With inline assembly: " << result << endl << endl;

	//****PART B****

	cout << "Part B:" << endl;
	cout << "Without inline assembly: " << (num1 + num2) / 3 << endl;
	__asm
	{
		;was expecting overflow of regisiters...using unsigned however
		mov edx, 0			;clear reg
		mov eax, num2		;eax = num1
		add eax, num1		;edx:eax = num1+num2
		idiv THREE			;eax = edx:eax/3
		mov result, eax		;result = eax
	}

	cout << "With inline assembly: " << result << endl << endl;

	//****PART C*****

	cout << "Part C:" << endl;
	cout << "Without inline assembly: " << (num1 * 30 - num2) / 14 << endl;
	__asm
	{
		mov eax, num1		;eax = 1 000 000 000
		imul THIRTY			;edx:eax = 30 000 000 000
		mov result, eax
		sub eax, num2		
		sbb edx, 0			;account for possible borrow from low order bits
		idiv FOURTEEN		;eax = edx:eax / 14
		mov result, eax		;result = eax
	}

	cout << "With inline assembly: " << result << endl << endl;

	//****PART D*****

	cout << "Part D: " << endl;
	cout << "Without inline assembly: " << (num1 * 53 - num2 * 30) / 7 << endl;
	__asm
	{
		mov eax, num2
		imul THIRTY	;edx:eax = 60 000 000 000

		;want to preserve edx:eax pair by storing into ebx:ecx pair
		mov ecx, eax
		mov ebx, edx				;ebx:ecx = 60 000 000 000

		mov eax, num1
		imul FIFTY_THREE			;edx:eax = 53 000 000 000


		sub eax, ecx				;edx:eax = (ebx:ecx) - (edx:eax)
		sbb edx, ebx

		idiv SEVEN					;eax = edx:eax / 7

		mov result, eax				;result = eax

	}

	cout << "With inline assembly: " << result << endl << endl;

}

/*
OUTPUT:

Part A:
Without inline assembly: 282013081
With inline assembly: 2000000000

Part B:
Without inline assembly: -431655765
With inline assembly: 1000000000

Part C:
Without inline assembly: -147483648
With inline assembly: 2000000000

Part D:
Without inline assembly: 227133513
With inline assembly: -1000000000

Press any key to continue . . .

*/
