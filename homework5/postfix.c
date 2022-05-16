#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack ������ �켱������ ��������, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE]; //infix ǥ��
char postfixExp[MAX_EXPRESSION_SIZE]; //postfix ǥ��
char postfixStack[MAX_STACK_SIZE]; //���� �迭
int evalStack[MAX_STACK_SIZE]; //eval ���� �迭

int postfixStackTop = -1; //���� �迭 top �ʱⰪ = -1
int evalStackTop = -1; //eval ���� �迭 top �ʱⰪ = -1

int evalResult = 0; //����� ������ ����

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command; //�޴� �Է� ����

   printf("[----- [������]  [2021041075] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default: //���� ���� ���� �ԷµǾ��� ��� ��� �޼��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q�� Q�� ���� ��� �ݺ��� ����

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; //������ top�� 1 ������Ű�� �� ��ġ�� x�� ����
}

//pop : ���ÿ��� ������
char postfixPop()
{
	char x;
    if(postfixStackTop == -1) //������ top�� -1�� ���
        return '\0'; //\0�� ��ȯ
    else { //�ƴѰ��
    	x = postfixStack[postfixStackTop--]; //������ top���� x�� ������ �Ŀ� top �� -1
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; //eval ������ top�� ���� 1 ������Ű�� �� top�� ��ġ�� ���ÿ� x �� ����
}

//eval ���� �� pop�ϱ�(����)
int evalPop()
{
    if(evalStackTop == -1) //eval ������ top�� -1�� ���
        return -1; //�Լ� ��
    else //�ƴ� ���
        return evalStack[evalStackTop--]; //eval ������ top ��ġ�� �� ��ȯ�� �Ŀ� top -1
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); //����ڷκ��� infix ǥ����� �Է¹��� -> �װ� infixExp�� ����
}

//���� ��Ʈ�����κ��� ��ū ���
precedence getToken(char symbol)
{
    //symbol�� ���� ǥ���̸�, token�� �װ��� ���ŵ� ������ ǥ���ǰ� ��Ī���� ��ȯ�Ѵ�
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand; //���� �˻� ���� �ʰ� �⺻ ���� �ǿ�����
	}
}

precedence getPriority(char x)
{
	return getToken(x); //���� ��Ʈ�����κ��� ��ū ��� ���� �Լ� ȣ�� �� �� ��ȯ
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0') //postfixExp�� \0�� ��� (�� ����)
		strncpy(postfixExp, c, 1); //c ���ڸ� postfixExp�� �����ϴµ� 1��ŭ�� ����
	else
		strncat(postfixExp, c, 1); //c ���� 1���� postfixExp ���ʿ� �̾� ���̱�
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0') //exp�� ���� \0�� �ƴ� ������ �ݺ�
	{
        //������ exp�� ����Ű�� ���ڰ� �ǿ������� ���
		if(getPriority(*exp) == operand) 
		{
			x = *exp;    //������ exp�� ����Ű�� ���� x�� ����
        	charCat(&x); //charCat�Լ��� x�� �ּ� ���� (postixExp�� ������ ����)
		}
        //������ exp�� ����Ű�� ���ڰ� '('�� ���
        else if(getPriority(*exp) == lparen) {
        	postfixPush(*exp); //���ÿ� ����
        }
        //������ exp�� ����Ű�� ���ڰ� ')'�� ���
        else if(getPriority(*exp) == rparen)
        {
            //������ ��ȣ�� ������ ���� ��ȣ�� ���� ������ pop
        	while((x = postfixPop()) != '(') {
        		charCat(&x); //postfixExp�� ����
        	}
        }
        //������ exp�� ����Ű�� ���ڰ� �������� ���
        else
        {
            //������ top�� �ִ� �����ڰ� exp�� ����Ű�� �����ں��� �켱������ ���ų� ���� ��� �ݺ�
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
            {
            	x = postfixPop(); //���� ������ top���� pop�ؼ� x�� ����
            	charCat(&x); //x���� postfixExp�� �߰�
            }
			//exp�� ����Ű�� �����ڰ� �켱������ ���� ���
            postfixPush(*exp); //exp�� ����Ű�� ������ ���ÿ� ����
        }
        exp++; //exp +1 ����
	}

    //������ top�� -1�� �ƴ� ������ �ݺ� = ���� �� ��������
    while(postfixStackTop != -1)
    {
    	x = postfixPop(); //���ÿ��� top���� ������
    	charCat(&x); //postfixExp�� �߰�
    }

}

//infixExp, postfixExp, evalResult, postfixStack ���
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);     //infixExp ���
	printf("postExp =  %s\n", postfixExp);    //postfixExp ���
	printf("eval result = %d\n", evalResult); //evalResult ���

    //postfixStack ���
	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

//infixExp, postfixExp, evalResult, postfixStack �ʱ�ȭ
void reset()
{
	infixExp[0] = '\0';   //infixExp �ʱ�ȭ
	postfixExp[0] = '\0'; //postfixExp �ʱ�ȭ

    //postfixStack �ʱ�ȭ
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1; //���� top -1
	evalStackTop = -1;    //eval ���� top -1
	evalResult = 0;       //evalResult 0
}

//���� ǥ��� ���갪
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp); //postfixExp�� ���� length�� ����
	char symbol;
	evalStackTop = -1;

    //0~length-1���� �ݺ�
	for(i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
        //symbol�� ����Ű�� ���� �ǿ����� �� ���
		if(getToken(symbol) == operand) {
			evalPush(symbol - '0');
            //symbol�� char �ڷ����̹Ƿ� 0�� �ƽ�Ű �ڵ� 10���� �� 48�� ���� ���ڸ� ���� �� ���� - ���� ����
		}
		else {
            //�� �ǿ����ڸ� �����Ͽ� ������ ������ ��, �� ����� ���ÿ� ����

            //���ÿ��� �� �� �� ����
			opr2 = evalPop();
			opr1 = evalPop();

			switch(getToken(symbol)) {
			case plus: evalPush(opr1 + opr2); break;   //���� ���� -> ���ؿ� ����
			case minus: evalPush(opr1 - opr2); break;  //���� ���� -> ���ؿ� ����
			case times: evalPush(opr1 * opr2); break;  //���� ���� -> ���ؿ� ����
			case divide: evalPush(opr1 / opr2); break; //������ ���� -> ���ؿ� ����
			default: break;
			}
		}
	}
	evalResult = evalPop(); //��� ��ȯ
}