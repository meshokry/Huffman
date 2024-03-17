#include <stdio.h>
#include <stdlib.h>

typedef struct element element;

struct element{

float probability;
char symbol;

};

//This function arrange the array in descending order

void reorder_the_array(element**arr,int number_of_inputs)
{
    int counter1,counter2,container1,container2;
    element temp;

    for(counter1=0;counter1<number_of_inputs-1;counter1++)
    {
       for(counter2=counter1+1;counter2<number_of_inputs;counter2++)
       {
           //using containers to avoid comparing between two float values
           container1=(int)(((*arr)[counter2].probability)*10000);
           container2=(int)(((*arr)[counter1].probability)*10000);
           if(container1>container2)
           {
               //swapping
               temp=(*arr)[counter2];
              (*arr)[counter2]=(*arr)[counter1];
              (*arr)[counter1]=temp;
           }
       }
    }
}

void print_table(element**arr,int number_of_inputs)
{
    int column,row;
    for(row=0;row<number_of_inputs;row++)
    {
        for(column=0;column<number_of_inputs-row;column++)
        {
          if(row!=0||column!=number_of_inputs-1)
          {
              printf("%c = %f      ",arr[column][row].symbol,arr[column][row].probability);
          }
        }
       printf("\n");
    }
     printf("\n");
}

void build_new_coulmn(element**arr,int number_of_inputs,int column)
{
    int row=0;
    arr[column]=(element*)malloc((number_of_inputs-column)*sizeof(element));
    for(row=0;row<((number_of_inputs-column-1));row++)
    {
        arr[column][row]=arr[column-1][row];
    }
    arr[column][row].probability=arr[column-1][row].probability+arr[column-1][row+1].probability;
    arr[column][row].symbol=129+column;//arr[column-1][row].symbol;//+arr[column-1][row+1].symbol;

}

void get_and_swap(element** arr,int column,int row,int number_of_inputs)
{
    int counter;
    element temp;
    for(counter=0;counter<number_of_inputs-column-1;counter++)
    {
        if(arr[column][row].symbol==arr[column+1][counter].symbol)
        {
         arr[column][row].probability=arr[column+1][counter].probability;

               if(counter!=number_of_inputs-(column+1)-1)//to not swap if it is the last element in the array
               {
                       temp=arr[column+1][counter];
                       arr[column+1][counter]=arr[column+1][counter+1];
                       arr[column+1][counter+1]=temp;
               }
        }

    }


}

void assign_zero(element*arr)
{
    arr->probability=arr->probability*10+2;/*adding 2 to represent zero*/
}

void assign_one(element*arr)
{
    arr->probability=arr->probability*10+1;/*adding 1 to represent one*/
}

int get_tens(int number)
{
    int counter=1;

    while(number/10!=0)
    {
        number/=10;
        counter=counter*10;
    }
    return counter;
}

int main()
{
/*****************************************************************/
                  /*constructing the table*/

    int number_of_inputs,column,row;

/*Taking number of inputs from user*/
    printf("Enter number of values\n");
    scanf("%d",&number_of_inputs);

/*creating the seed of the table*/
    element**arr=(element**)malloc((number_of_inputs-1)*sizeof(element*));

/*Creating First Column in the table*/
    arr[0]=(element*)malloc(number_of_inputs*sizeof(element));

/*Getting symbols & probabilities from user*/
   for(row=0;row<number_of_inputs;row++)
    {
        printf("Enter symbol %d\n",row+1);
        scanf(" %c",&arr[0][row].symbol);
        printf("Enter probability %d\n",row+1);
        scanf("%f",&arr[0][row].probability);
    }
/*rearrange first column*/
    reorder_the_array(&arr[0],number_of_inputs);


/*creating the rest of the table like lecture*/
    for(column=1;column<number_of_inputs-1;column++)
    {
     build_new_coulmn(arr,number_of_inputs,column);
     reorder_the_array(&arr[column],number_of_inputs-column);
    }

/*printing table like lecture*/
print_table(arr,number_of_inputs);

/*******************************************************************************/
                      /*assigning codes to table*/


/*assigning zero and one to last column*/
arr[number_of_inputs-2][0].probability=2;      /*2 means zero*/
arr[number_of_inputs-2][1].probability=1;      /*1 means one*/


/*return back on each column and put the value of the code*/
for(column=number_of_inputs-3;column>=0;column--)
{

   for(row=0;row<number_of_inputs-column;row++)
   {
       /*if it is the element before the last one in the column so it will take the probability of first element from next column and add zero to it*/
       if(row==number_of_inputs-column-2)
       {
           arr[column][row].probability=arr[column+1][0].probability;
           assign_zero(&arr[column][row]);
       }
       /*if it is the last element in the column one so it will take the probability of first element from next column and add one to it*/
       else if(row==number_of_inputs-column-1)
       {
           arr[column][row].probability=arr[column+1][0].probability;
           assign_one(&arr[column][row]);
       }
       /*search about the element in the next column and get the probability from it then drag it down by one*/
       else
       {
        get_and_swap(arr,column,row,number_of_inputs);
       }

   }


}
/********************************************************************************/
                              /*printing code*/

int digit,tens;

for(row=0;row<number_of_inputs;row++)
{
    tens = get_tens((int)arr[0][row].probability);

    printf("%c = ",arr[0][row].symbol);

    while(tens!=0)
    {
        digit=(((int)(arr[0][row].probability))/tens);/*getting digit through dividing on ten multiplied by number of digits minus one*/

        (digit>1)?printf("0"):printf("1");/*if the digit equal 2 print 0 and if digit equals 1 print 1*/

        (arr[0][row].probability)=((int)(arr[0][row].probability))-digit*tens;/*deleting digit after checking it*/

        tens/=10;   /*reducing it by digit*/
    }
    printf("\n");
}

system("pause");

        return 0;
}


