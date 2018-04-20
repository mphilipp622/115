#ifndef TURNMANAGER_H
#define TURNMANAGER_H


// in charge of managing player and enemy turns. Created as a global class so player and GLScene can both access it to get and set turns
class TurnManager
{
    public:
        TurnManager();
        virtual ~TurnManager();

        // returns true if current turn is player turn
        bool IsPlayerTurn();

        // returns true if current turn is enemy turn
        bool IsEnemyTurn();

        // ends current turn and goes to next turn
        void NextTurn();

        // global instance of class
        static TurnManager* turnManager;

    protected:

    private:

        bool turn; // player turn is 0, enemies is 1
};

#endif // TURNMANAGER_H
