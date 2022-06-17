#include <stdio.h>
#include <stdlib.h>

struct Clothes {
    char company[51];
    char model[51];
    char size[11];
    char collection[51];
    char fabric[21];
    int price;
    int stock;
};

int main()
{
    struct Clothes C[50];
    int i=0, deletion=-1, buy=-1, item=-1, howmuch=-1;

    FILE *file;
    file = fopen("db.txt", "r");

    char buffer[200];

    while(!feof(file)) {
        fgets(buffer, 200, file);
        struct Clothes* c = C + i;
        sscanf(buffer, "%s %s %s %s %s %i %i", &c->company, &c->model, &c->size, &c->collection, &c->fabric, &c->price, &c->stock);
        i++;
    }
    i--;

    fclose(file);

    int menu;
    do {
        printf("1 - List Clothes\n2 - Add an article of clothing\n3 - Remove an article of clothing\n4 - Buy an Article of Clothing\n5 - Add new stock\n0 - Save & Exit\nYour selection: ");
        scanf("%d", &menu);
        system("cls");
        switch(menu) {
            case 1:
                printf("\n");
                printf("1 - Show All Articles\n2 - Only Articles in Stock\n3 - Only Articles out of Stock\nYour Selection: ");
                int show;
                scanf("%d", &show);
                switch(show) {
                    case 1:
                        for (int j=0; j<i; j++)
                            printf("%i: %s %s %s %s %s %i %i\n", j, C[j].company, C[j].model, C[j].size, C[j].collection, C[j].fabric, C[j].price, C[j].stock);
                        break;
                    case 2:
                        for (int j=0; j<i; j++)
                            if (C[j].stock>0)
                                printf("%i: %s %s %s %s %s %i %i\n", j, C[j].company, C[j].model, C[j].size, C[j].collection, C[j].fabric, C[j].price, C[j].stock);
                        break;
                    case 3:
                        for (int j=0; j<i; j++)
                            if (C[j].stock==0)
                                printf("%i: %s %s %s %s %s %i %i\n", j, C[j].company, C[j].model, C[j].size, C[j].collection, C[j].fabric, C[j].price, C[j].stock);
                        break;
                    default:
                        printf("Invalid Option. Cancelling.\n");
                }
                break;
            case 2:
                printf("\nEnter the company name: ");
                scanf("%s", &C[i].company);

                printf("Enter the model: ");
                scanf("%s", &C[i].model);

                printf("Enter the size: ");
                scanf("%s", &C[i].size);

                printf("Enter the collection: ");
                scanf("%s", &C[i].collection);

                printf("Enter the fabric: ");
                scanf("%s", &C[i].fabric);

                printf("Enter the price: ");
                scanf("%i", &C[i].price);

                printf("How much do you have in stock?: ");
                scanf("%i", &C[i].stock);
                printf("Added successfully:\n%i: %s %s %s %s %s %i %i\n", i, C[i].company, C[i].model, C[i].size, C[i].collection, C[i].fabric, C[i].price, C[i].stock);
                i++;
                break;
            case 3:
                printf("Which item do you want to delete? ( 0 - %i ): ", i-1);
                scanf("%i", &deletion);
                printf("Deleting: %s %s %s %s %s %i %i\n", C[deletion].company, C[deletion].model, C[deletion].size, C[deletion].collection, C[deletion].fabric, C[deletion].price, C[deletion].stock);
                for (int j=deletion; j<i-1; j++)
                    C[j] = C[j+1];
                i--;
                printf("Deleted\n");
                break;
            case 4:
                printf("Which item do you want to buy? ( 0 - %i ): ", i-1);
                scanf("%i", &buy);
                if (C[buy].stock > 0) {
                    C[buy].stock -= 1;
                    printf("Bought: %s %s %s %s %s \nAt price: %i \nRemained Stock: %i \n", C[buy].company, C[buy].model, C[buy].size, C[buy].collection, C[buy].fabric, C[buy].price, C[buy].stock);
                } else printf("There isn't enough of this item in the store.");
                break;
            case 5:
                printf("Which item did you receive? ( 0 - %i ): ", i-1);
                scanf("%i", &item);
                printf("How many?: ");
                scanf("%i", &howmuch);
                C[item].stock += howmuch;
                break;
            case 0:
                file = fopen("db.txt", "w");

                for(int j=0; j<i; j++)
                    fprintf(file, "%s %s %s %s %s %i %i\n", C[j].company, C[j].model, C[j].size, C[j].collection, C[j].fabric, C[j].price, C[j].stock);

                fclose(file);
                break;
            default:
                printf("Invalid Option.");
        };
        printf("\n");
    } while (menu!=0);
    return 0;
}
