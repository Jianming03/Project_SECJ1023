#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const int userSize = 5;

class Energy;
class Maintenance;

class User {
    private:
        string user[userSize];
        string password[userSize];
        char response;
        Energy *energy;
        Maintenance *maintain;
        int userCount;
    
    public:
        User() : userCount(0), energy(nullptr), maintain(nullptr) {}
    
        void registerUser() {
            if(userCount < userSize) {
                string userId, pass;
                cout << "Enter User Id: ";
                cin >> userId;
                cout << "Enter Password: ";
                cin >> pass;

                user[userCount] = userId;
                password[userCount] = pass;
                userCount++;
                cout << "User registered successfully!" << endl;
            } 
            else {
                cout << "Number of Registered Users has reached max capacity" << endl;
            }
        }

        bool checkUser(string userId, string pass) {
            for(int i = 0; i < userCount; i++) {
                if((user[i] == userId) && (password[i] == pass)) {
                    return true;
                }
            }
            return false;
        }

        bool login() {
            string id, pass;
            cout << "User Id: ";
            cin >> id;
            cout << "Password: ";
            cin >> pass;

            if(checkUser(id, pass)) {
                cout << "Login successful!" << endl;
                return true;
            } 
            else {
                cout << "Invalid id or password. Please enter again." << endl;
                return false;
            }
        }

        bool logOut() {
            cout << "Do you want to log out? (Y/N)" << endl;
            cin >> response;
            if(response == 'Y' || response == 'y') {
                cout << "Logout successful!" << endl;
                return true;
            } 
            else if(response == 'N' || response == 'n') {
                return false;
            }
        }

        void displayLogInMenu() {
            cout << "\n===== Helios Solar Panel System =====" << endl;
            cout << "1. Register" << endl;
            cout << "2. Log In" << endl;
            cout << "3. Exit" << endl;
            cout << "=====================================" << endl;
        }

        void displayMainMenu() {
            cout << "\n===== Helios Solar Panel System =====" << endl;
            cout << "1. Solar Panel Information" << endl;
            cout << "2. Financial Tracking" << endl;
            cout << "3. Energy Tracking" << endl;
            cout << "4. Installment" << endl;
            cout << "5. Maintenance" << endl;
            cout << "6. Log Out" << endl;
            cout << "=====================================" << endl;
        }

        friend ostream &operator<<(ostream &stream, const Energy &energy);
        friend ostream &operator<<(ostream &stream, const Maintenance &main);
};

class Installment {
    private:
        double totalCost;
        double monthlyInstallment;
        int year;
        double interestRate;

    public:
        Installment(double cost = 0, double int_rate = 0, int y = 0) : totalCost(cost), interestRate(int_rate), year(y) {}

        void calculateInstallment() {
            cout << "\nInstallment Calculator" << endl;
            cout << "Price: ";
            cin >> totalCost;
            cout << "Number of Years: ";
            cin >> year;
            cout << "Interest Rate: ";
            cin >> interestRate;
            for(int i = 0; i < year; i++) { // compounded interest
                totalCost += totalCost * interestRate;
            }
            monthlyInstallment = totalCost / (year * 12.0);
        }

        void showDetails() {
            cout << "Total cost: RM" << totalCost << endl;
            cout << "Monthly Installment: RM" << monthlyInstallment << endl;
            cout << "Duration: " << year << " year(s)" << endl;
            cout << "Interest Rate: " << interestRate << endl;
        }
};

class Maintenance {
    private:
        int num, day, month, year;
        string condition;

    public:
        Maintenance(int n = 0, string status = "") : num(n), condition(status), day(0), month(0), year(0) {}

        int calculateDay(int day1, int month1, int year1, int day2, int month2, int year2) {
            int days1 = year1 * 365 + day1;
            for(int i = 0; i < month1 - 1; i++) {
                days1 += 30;
            }

            int days2 = year2 * 365 + day2;
            for(int i = 0; i < month2 - 1; i++) {
                days2 += 30;
            }
            return abs(days2 - days1);
        }

        void calculateMonth(int &day, int &month, int &year, int addMonth) {
            month += addMonth;
            while(month > 12) {
                month -= 12;
                year += 1;
            }
        }

        void checkCondition(int lastDay, int lastMonth, int lastYear, int currentDay, int currentMonth, int currentYear) {
            int days = calculateDay(lastDay, lastMonth, lastYear, currentDay, currentMonth, currentYear);

            if(days > 0 && days <= 180) {
                condition = "green";
                cout << "Solar panel's health condition: green" << endl;
            } 
            else if (days > 180 && days <= 365) {
                condition = "yellow";
                cout << "Solar panel's health condition: yellow" << endl;
            } 
            else {
                condition = "red";
                cout << "Solar panel's health condition: red" << endl;
            }
        }

    void maintenanceDate(int currentDay, int currentMonth, int currentYear) {
        if(condition == "green") {
            calculateMonth(currentDay, currentMonth, currentYear, 6);
            num++;
            cout << "Your new maintenance date is on " << (currentDay < 10 ? "0" : "") << currentDay << "/" << (currentMonth < 10 ? "0" : "") << currentMonth << "/" << currentYear << endl;
        } else if(condition == "yellow") {
            calculateMonth(currentDay, currentMonth, currentYear, 3);
            num++;
            cout << "Your new maintenance date is on " << (currentDay < 10 ? "0" : "") << currentDay << "/" << (currentMonth < 10 ? "0" : "") << currentMonth << "/" << currentYear << endl;
        } else if(condition == "red") {
            cout << "You should maintain the panel immediately." << endl;
        }
    }

    int getNum() const {
        return num;
    }

    friend ostream &operator<<(ostream &stream, const Maintenance &main) {
        stream << "Maintenance Summary\nMaintenance count: " << main.num << "\nCondition: " << main.condition;
        return stream;
    }
};

class Energy {
    private:
        int hr;
        double UE; // Amount of Energy Used (Energy Bought and/or Produced)
        double PE; // Produced Energy
        double NE; // Net Energy = Energy Produced - Energy Used
        double ER; // Rate of Energy Produced kWh passed from Model type
        double CE; // Current Energy Levels of Energy Storage system
        double EP; // Energy Price
        double sales; // use for ROI
        double energySold; // use for energy savings
    
    public:
        Energy(int hour = 0, double usedE = 0, double _ER = 0, double _EP = 0) : hr(hour), UE(usedE), ER(_ER), EP(_EP), CE(0.0), energySold(0.0), sales(0.0) {}

        int getHr() const { return hr; }
        double getUE() const { return UE; }
        double getPE() const { return hr * ER; }
        double getNE() const { return getPE() - UE; }
        double getCE() const { return CE; }
        double getEP() const { return EP; }
        double getER() const { return ER; }
        double getSales() const { return sales; }
        double getEnergySold() const { return energySold; }

        void setHr(int hour) { hr = hour; }
        void setUE(double usedE) { UE = usedE; }
        void setPE(double prodE) { PE = prodE; }
        void setCE(double currE) { CE = currE; }
        void setEP(double energyPrice) { EP = energyPrice; }
        void setEnergySold(double _energySold) { energySold = _energySold; }
        void setSales(double _sales) { sales = _sales; }
        void setER(double _ER) { ER = _ER; }

        double sellEnergy(double energy) {
            return energy * EP;
        }

        void showEnergy() const {
            cout << "Current Energy Levels: " << CE << " kWh" << endl;
            cout << "Energy Used: " << UE << " kWh" << endl;
            cout << "Energy Rate: " << ER << " kWh" << endl;
            cout << "Produced Energy: " << getPE() << " kWh" << endl;
            cout << "Net Energy: " << getNE() << " kWh" << endl;
        }

        friend ostream &operator<<(ostream &stream, const Energy &energy) {
            stream << "Energy Summary\nEnergy Produced: " << energy.getPE() << "\nEnergy Used: " << energy.getUE() << "\nNet Energy: " << energy.getNE();
            return stream;
        }
};

class SolarPanel : public Energy {
    protected:
        string manufacturer;
        string model;
        double capacity; // kW
        double efficiency; // %
        int area; // m2
                
    public:
        SolarPanel(string _manufacturer = "Helios", string _model = "", double _capacity = 0, double _efficiency = 0.0, int _area = 0, double _ER = 0.0, double _EP = 0.0) : Energy(0, 0, _ER, _EP), manufacturer(_manufacturer), model(_model), capacity(_capacity), efficiency(_efficiency), area(_area) {}

        virtual void getDetails() {
            cout << "Manufacturer: " << manufacturer << endl;
            cout << "Model: " << model << endl;
            cout << "Capacity: " << capacity << " kW" << endl;
            cout << "Efficiency: " << efficiency << " %" << endl;
            cout << "Area: " << area << " sq. meters" << endl;
        }

        void manageEnergy() {
            for(int i = 1; i <= getHr(); i++) {
                setCE(getCE() + (1 * getER()) * efficiency);
                if (getCE() > capacity) {
                    double excessEnergy = getCE() - capacity;
                    setCE(capacity);
                    setEnergySold(getEnergySold() + excessEnergy);
                    setSales(getSales() + sellEnergy(excessEnergy));
                }
                cout << endl;
                cout << "#" << i << " hour: " << endl;
                cout << "Current Energy Level = " << getCE() << endl;
                cout << "Total Energy Sold = " << getEnergySold() << " kW" << endl;
                cout << "Total Sales = RM" << getSales() << endl;
            }
        }
};

class ModelA: public SolarPanel {
    protected:
        string type; // monocrytalline +15% efficiency, polycrystalline +5% efficiency
        bool bifacial; // true = bifacial(twosided), false = not bifacial
    
    public:
        ModelA(string _manufacturer = "Helios", string _model = "A", double _capacity = 300, double _efficiency = 25,
        int _area = 25, double _ER = 2.0, double _EP = 0.1, string _type = "mono", bool _bifacial = true)
        : SolarPanel(_manufacturer, _model, _capacity, _efficiency + 15, _area, _ER, _EP), type(_type), bifacial(_bifacial) {}

        void getDetails() override {
            SolarPanel::getDetails();
            cout << "Type: " << type << endl;
            cout << "Bifacial: " << (bifacial ? "Yes" : "No") << endl;
        }
};

class ModelB: public SolarPanel {
    protected:
        bool tracking; // allows panels to track the sun
        bool smart; // power optimizers and more accurate monitoring capability
    
    public:
        ModelB(string _manufacturer = "Helios", string _model = "B", double _capacity = 500, double _efficiency = 35,
        int _area = 15, double _ER = 5.0, double _EP = 2.0, bool _tracking = true, bool _smart = true)
        : SolarPanel(_manufacturer, _model, _capacity, _efficiency + 15, _area, _ER, _EP), tracking(_tracking), smart(_smart) {}

        void getDetails() override {
            SolarPanel::getDetails();
            cout << "Tracking: " << (tracking ? "Yes" : "No") << endl;
            cout << "Smart: " << (smart ? "Yes" : "No") << endl;
        }
};

int main() {
    User users;
    Installment install;
    Maintenance maintenance;
    ModelA panelA;
    ModelB panelB;
    panelA.setHr(5); // Set the number of sunlight hours
    panelA.setUE(50); // Set the amount of energy used
    panelB.setHr(5); // Set the number of sunlight hours
    panelB.setUE(100); // Set the amount of energy used

    int choice;

    do {
        users.displayLogInMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                users.registerUser();
                break;
                
            case 2:
                if (users.login()) {
                    int userChoice;
                    do {
                        users.displayMainMenu();
                        cout << "Enter Your Choice: ";
                        cin >> userChoice;
                        if(userChoice < 1 || userChoice > 6) {
                            cout << "Invalid choice, please enter again" << endl;
                            continue;
                        }
                        switch (userChoice) {
                            case 1: {
                                char selection;
                                cout << "\nModel A or B? : ";
                                cin >> selection;
                                if(selection == 'A') {
                                    panelA.getDetails();
                                } else if(selection == 'B') {
                                    panelB.getDetails();
                                }
                                break;
                            }
                            
                            case 2: {
                                char selection;
                                cout << "\nModel A or B? : ";
                                cin >> selection;
                                if(selection == 'A') {
                                    panelA.manageEnergy();
                                } else if(selection == 'B') {
                                    panelB.manageEnergy();
                                }
                                break;
                            }
                    
                            case 3: {
                                char selection;
                                cout << "\nModel A or B? : ";
                                cin >> selection;
                                if(selection == 'A') {
                                    panelA.showEnergy();
                                } else if(selection == 'B') {
                                    panelB.showEnergy();
                                }
                                break;
                            }

                            case 4: 
                                install.calculateInstallment();
                                install.showDetails();
                                break;
                            
                            case 5: {
                                int lastDay, lastMonth, lastYear;
                                int currentDay, currentMonth, currentYear;
                                char slash;
                                cout << "Enter your last maintenance date (DD/MM/YYYY): ";
                                cin >> lastDay >> slash >> lastMonth >> slash >> lastYear;
                                cout << "Today's date (DD/MM/YYYY): ";
                                cin >> currentDay >> slash >> currentMonth >> slash >> currentYear;
                                maintenance.checkCondition(lastDay, lastMonth, lastYear, currentDay, currentMonth, currentYear);
                                maintenance.maintenanceDate(currentDay, currentMonth, currentYear);
                                break;
                            }
                            
                            case 6:
                                if(users.logOut()) {
                                    userChoice = 6;
                                }
                                else {
                                    userChoice = 0;
                                }
                                break;       	
                        }
                    } while(userChoice != 6);
                }
                break;
                
            case 3:
                cout << "Exiting the system..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
    
    return 0;
}
