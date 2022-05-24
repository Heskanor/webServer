# include <iostream>
# include <string>

int  findfirstline(std::string *tab)
{
  std::string stringg[9];
  stringg[0] ="GET ";
  stringg[1] ="HEAD ";
  stringg[2] ="POST ";
  stringg[3] ="PUT ";
  stringg[4] ="DELETE ";
  stringg[5] ="CONNECT ";
  stringg[6] ="OPTIONS ";
  stringg[7] ="TRACE ";
  stringg[8] ="PATCH ";

  for (int i = 0; i <= 8 ; i++)
  {
    if (tab[0].find(stringg[i]) != std::string::npos)
    {
        std::cout<<tab[0].find(stringg[i])<<std::endl;
        return(tab[0].find(stringg[i]));
    }
  }
  return(0);
}

int main()
{
    std::string tab[2];
  //  std::cout<<"allo im here "<<std::endl;
    tab[0] = "        2GET ";
    findfirstline(tab);


}