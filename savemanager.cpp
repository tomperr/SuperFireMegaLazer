#include "savemanager.hpp"

vector<string> lireSauvegardeScore(string const& path)
{
    // Lit le fichier de sauvegarde
    vector<string> lines;
    string line;
    ifstream save(path.c_str());
    if(save.is_open())
    {
        while(getline(save, line))
        {
            lines.push_back(line);
        }
    }

    return lines;
}

vector<int> convertSauvegardeScore(vector<string> scores)
{
    // Convertit une liste de string en liste de int
    vector<int> convert;
    int scoreConvert;
    for(int i(0); i<scores.size(); i++)
    {
        scoreConvert = str2int(scores[i]);
        convert.push_back(scoreConvert);
    }
    return convert;
}

void tri_bulles(vector<int> &scores)
{
    // Bubble sort d'une liste de int
    bool ordered = false;
    int size = scores.size();
    while(!ordered)
    {
        ordered = true;
        for(int i=0 ; i < size-1 ; i++)
        {
            if(scores[i] > scores[i+1])
            {
                swap(scores[i],scores[i+1]);
                ordered = false;
            }
        }
        size--;
    }
}

void enregistrerSauvegardeScore(string path, int score)
{
    // Ecrit un score dans un fichier de sauvegarde
    vector<int> scores = convertSauvegardeScore(lireSauvegardeScore(path.c_str()));
    scores.push_back(score);
    tri_bulles(scores);

    ofstream save(path.c_str());
    if(save.is_open())
    {
        for(int i(0); i<scores.size(); i++)
        {
            save << scores[i] << endl;
        }
    }

}

int str2int (string str)
{
    // Convertit un string en int
    stringstream ss(str);
    int num;
    if((ss >> num).fail())
    {
        //ERROR
    }
    return num;
}

void resetSauvegardeScore(string path)
{
    // Reset le fichier de sauvegarde
    ofstream save(path.c_str());
}
