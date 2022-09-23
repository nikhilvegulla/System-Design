#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<string>
#include<unordered_map>

using namespace std;



class Mail{
    public:
    Mail(vector<string> mail={},string sub="",string body="",string from="");
    
vector<string> mail;
string from;
string sub;
string body;
};

Mail :: Mail(vector<string> mail,string sub,string body,string from)
{
    for(int i=0;i<mail.size();i++)
    {
        this->mail.push_back(mail[i]);
    }
    this->sub=sub;
    this->from=from;
    this->body=body;
}
class User{
    private:
    string name;
    string gmail;
    public:
    vector<Mail> inbox;
    vector<Mail> unread;
    vector<Mail> starred;
    vector<Mail> draft;
    vector<Mail> sent;
    vector<Mail> spam;
    // vector<vector<Mail>> labels;
    unordered_map<string,vector<Mail>> labels;

    //methods
    User(string name,string gmail);
    void getinbox();
    void getunread();
    void getdraft();
    void getstarred();
    void makestarred();
    void getsent();
    void sentmail();
    void deletesent();
    void displayspam();
    void makespam();
    void forward();
    void makelabels();
    void displaylabels();
};

string Ggmail;
unordered_map<string,User> account;
unordered_map<string,string>account_pw;


//inbox
void User :: getinbox()
{
    int n=inbox.size();
    if(n==0)
    {
        cout<<"No mails "<<endl<<endl;
        return ;
    }
    for(int i=n-1;i>=0;i--)
    {
        // Mail o=inbox[]
        cout<<i<<" : "<<inbox[i].from<<" -> : "<<inbox[i].sub<<endl;
    }
}
//unread
void User::makelabels()
{
    int ch;
    cout<<"Create label or 2.move to existing : ";
    cin>>ch;
    string lab="";
    if(ch==2)
    {
        // string lab;
        cout<<"Enter label : ";
        cin>>lab;
        labels[lab]={};
        
    }
    if(lab=="")
    {cout<<"enter label : ";
    cin>>lab;}
    int n,id;
    cout<<"Enter n : ";
    cin>>n;
    while(n--)
    {
        cout<<"Enter id : ";
        cin>>id;
        if(id>=this->inbox.size())
            return;
        labels[lab].push_back(inbox[id]);

    }

}

//labels
void User::displaylabels()
{
    for(auto &i:labels)
    {
        cout<<i.first<<" : ";
        for(int j=0;j<i.second.size();j++)
         cout<<i.second[j].sub<<" ";

         cout<<endl;
    }
}

//getunread
void User :: getunread()
{
    int n=unread.size();
    if(n==0)
    {
        cout<<"No mails present>>"<<endl;
        return ;
    }
    for(int i=n-1;i>=0;i--)
    {
        cout<<i<<" : "<<unread[i].sub<<endl;
    }
    int i;
    cout<<"Do u want to read yes(1) or no(0) : ";
    cin>>i;
    if(i)
    {
        int id;
        cout<<"Enter ID: ";
        cin>>id;
        cout<<"From : "<<this->unread[id].from<<endl;
        cout<<"Sub : "<<this->unread[id].sub<<endl;
        cout<<"Body : "<<this->unread[id].sub<<endl;
        vector<Mail> :: iterator it;
        it=this->unread.begin()+id;
        this->unread.erase(it);
    }
}

//delete the sent mails
void User::deletesent()
{
    int id;
    cout<<"Enter id : ";
    cin>>id;
    if(id>=this->sent.size())
    {
        cout<<"Not found "<<endl;
        return;
    }
    this->sent.erase(this->sent.begin()+id);
}

//display draft msgs
void User :: getdraft()
{
    int n=draft.size();
    if(n==0)
    {
        cout<<"No mails >>"<<endl;
        return ;
    }
    for(int i=n-1;i>=0;i--)
    {
        cout<<"Index : "<<i<<endl;
        // cout<<"From : "<<this->draft[i].from<<endl;
        int j=draft[i].mail.size();
        cout<<"TO : "<<endl;
        while(j--)
        {
            cout<<this->draft[i].mail[j]  <<" | ";
        }
        cout<<endl;
        cout<<"Sub : "<<this->draft[i].sub<<endl;
        cout<<"Body : "<<this->draft[i].sub<<endl<<endl;
    }
    int ch;
    cout<<"Do u want to edit mail yes(1) || no(0): ";
    cin>>ch;
    if(ch)
    {
        int id;
        cout<<"Enter the id : ";
        cin>>id;
        Mail o=this->draft[id];
        cout<<"Enter the add subject (if nthg press enter) : ";
        string ad;
        fflush(stdin);
        getline(cin,ad);
        o.body+=" "+ad;
        for(int i=0;i<o.mail.size();i++)
        {
        account[o.mail[i]].unread.push_back(o);
        account[o.mail[i]].inbox.push_back(o);
        }
    this->draft.erase(this->draft.begin()+id);
    this->sent.push_back(o);
    cout<<"Sent successfully"<<endl;
    }
}

//display sent mails
void User :: getsent()
{
    int n=sent.size();
    if(n==0)
    {
        cout<<"No mails !!"<<endl;
        return ;
    }
    for(int i=n-1;i>=0;i--)
    {       
        // cout<<i<<" : "<<sent[i].sub<<endl;
        cout<<"Index : "<<i<<endl;
        // cout<<"From : "<<this->sent[i].from<<endl;
        int j=sent[i].mail.size();
        cout<<"TO : "<<endl;
        while(j--)
        {
            cout<<this->sent[i].mail[j]  <<" | ";
        }
        cout<<endl;
        cout<<"Sub : "<<this->sent[i].sub<<endl;
        cout<<"Body : "<<this->sent[i].body<<endl<<endl;
    }
}

//make the mails starred
void User :: makestarred()
{
    int id;
    cout<<"Enter id : ";
    cin>>id;
    Mail o=this->inbox[id];
    this->starred.push_back(o);

}

//display starred mails
void User :: getstarred()
{
    int n=starred.size();
    if(n==0)
    {
        cout<<"No mails present >>"<<endl;
        return ;
    }
    for(int i=n-1;i>=0;i--)
    {
        cout<<"Index : "<<i<<endl;
        cout<<"From : "<<this->starred[i].from<<endl;
        cout<<"Sub : "<<this->starred[i].sub<<endl;
        cout<<"Body : "<<this->starred[i].sub<<endl<<endl;
    }
}

//sending mails

void User::sentmail()
{
    int n;
    cout<<"Enter the Num of receiptants : ";
    cin>>n;
    vector<string> mailid(n);
    cout<<"Enter mail id : "<<endl;
    while(n--)
    {
        cin>>mailid[n];
        if(account.find(mailid[n])==account.end())
            {
                cout<<"InCorrect email : "<<endl;
                n+=1;
            }
    }
    string subject,body;
    // getline(cin,subject);
    fflush(stdin);
    cout<<"Enter subject : ";
    getline (cin, subject);
    // cin>>sub;
    cout<<"Enter body : ";
    getline (cin, body);
    // cin>>b;
    // cout<<body<<endl<<subject<<endl;
    Mail m(mailid,subject,body,Ggmail);
    int i;
    cout<<"1.send || 2.safe as draft : ";
    cin>>i;
    if(i==2)
    {
        this->draft.push_back(m);
        return;
    }
    for(int i=0;i<mailid.size();i++)
    {
        account[mailid[i]].unread.push_back(m);
        account[mailid[i]].inbox.push_back(m);
    }
    this->sent.push_back(m);
    
}

//displas the spam msgs
void User :: displayspam()
{
    int n=spam.size();
    // cout<<"Length of spam mails: "<<n<<endl;
    if(n==0)
    {
        cout<<"No mails >>"<<endl;
        return ;
    }
    for(int i=n-1;i>=0;i--)
    {
        // Mail o=inbox[]
        cout<<i<<" : "<<spam[i].sub<<endl;
    }
}


//make the spam msgs
void User::makespam()
{
    int id;
    cout<<"Enter id : ";
    cin>>id;
    Mail o=this->inbox[id];
    this->spam.push_back(o);
    this->inbox.erase(this->inbox.begin()+id);
}


// forward the msgs
void User::forward()
{
    int id,n;
    cout<<"Enter id : ";
    cin>>id;
    // Mail o=account[Ggmail].inbox[id];
    cout<<"Enter num of mail: ";
    cin>>n;
    Mail m=this->inbox[id];
    vector<string> mailid(n);
    cout<<"Enter mail id : "<<endl;
    while(n--)
    {
        cin>>mailid[n];
    }
    for(int i=0;i<mailid.size();i++)
    {
        account[mailid[i]].unread.push_back(m);
        account[mailid[i]].inbox.push_back(m);
    }
    this->sent.push_back(m);

}

//constructor
User :: User(string name="",string gmail="")
{
    this->gmail=gmail;
    this->name=name;

}

//login
bool login(string ac,string pw)
{
    if(account_pw.find(ac)==account_pw.end())
    return false;

    if(account_pw[ac]!=pw)
        return false;

    return true;
}

//signup
void signup()
{
    string n,gm,pw,cp="";
    cout<<"Name :";
    cin>>n;
    cout<<"Gmail :";
    cin>>gm;
    cout<<"password :";
    cin>>pw;

    while(cp!=pw)
    {
        cout<<"Confirm password: ";
        cin>>cp;
    }
    User u(n,gm);
    account[gm]=u;
    account_pw[gm]=pw;
}

//basic func
void filldetails()
{
    vector <string>names {"Nikhil","harika","Nikhitha","Swetha"};
    vector <string> gmail {"nikhil@gmail.com","harika@gmail.com","nikhitha@gmail.com","swetha@gmail.com"};
    vector <string> pw {"a","b","c","d"};
    for(int i=0;i<4;i++)
    {
        User u(names[i],gmail[i]);
        account[gmail[i]]=u;
        account_pw[gmail[i]]=pw[i];
    }
}


int main()
{
    filldetails();
    int oc=0;
    string gm,pw;

    while(oc<3)
    {
        cout<<"1.Login \n2.SignUp \nAny other num to exit"<<endl;
        cin>>oc;

        switch (oc)
        {
        case 1:
            {
                cout<<"Enter gmail: ";
                cin>>gm;
                cout<<"Enter Password: ";
                cin>>pw;
                
                if(!login(gm,pw))
                {
                      cout<<"Incorrect details : " <<endl;
                      continue;
                }
                        Ggmail=gm;

                        cout<<"login Successfull !!"<<endl;
                        User l=account[Ggmail];
                        cout<<"**** INBOX  *****"<<endl;
                        l.getinbox();
                    int c=0;
                    string p;
                        while(c!=-1)
                        {
                            // cout<<"1.Unread || 2.Starred || 3.draft || 4.Sentmails || 5.Compose || 6.make star ||7.logout || 8.Delete sent || 9.Inbox || 10.Forward || 11.change password || 12.Delete account || 13.mark as Spam || 14.Display Spam"<<endl;
                            cout<<"1.Unread mails       8.Display Inbox"<<endl;
                            cout<<"2.Starred mails      9.Logout"<<endl;
                            cout<<"3.Draft mails        10.Forward mail"<<endl;
                            cout<<"4.Sent mails         11.Change details"<<endl;
                            cout<<"5.Compose mail       12.Delete account"<<endl;
                            cout<<"6.Make Star          13.Marks as spam"<<endl;
                            cout<<"7.Delete sent mail   14.display spam"<<endl;
                            cout<<"\n Enter your choice :  ";
                            cin>>c;
                            if(c>14)
                                {
                                    cout<<"Enter correct choice : " <<endl<<endl;
                                    continue;
                                }
                            switch (c)
                            {
                            case 1:
                                {
                                    cout<<"****  UNREAD MAILS  *****"<<endl;
                                    l.getunread();
                                }
                                break;
                            case 2:
                            {
                                cout<<"****  STARRED MAILS  *****"<<endl;
                                l.getstarred();
                                break;
                            }
                            case 3:
                                cout<<"****  DRAFT MAILS  *****"<<endl;
                                l.getdraft();break;
                            case 4: 
                                cout<<"****  SENT MAILS  *****"<<endl;
                                l.getsent();break;
                            case 5:
                                l.sentmail();
                                cout<<"Composed successfully"<<endl;
                                break;
                            case 6:
                                l.makestarred();
                                cout<<"Marked as starred"<<endl;
                                break;
                            case 9:
                                Ggmail="";
                                c=-1;
                                cout<<"Successfully LoggedOut"<<endl;
                                break;
                            case 7:
                                l.deletesent();
                                cout<<"Mail deleted"<<endl;
                                break;
                            case 8:
                            cout<<"**** INBOX  *****"<<endl;
                                l.getinbox();
                                break;
                            case 10:
                                l.forward();
                                break;
                            case 11:
                                
                                cout<<"enter new  password : ";
                                cin>>p;
                                account_pw[Ggmail]=p;
                                cout<<"Passsword updated : "<<endl;
                                break;
                            case 12:
                                account.erase(Ggmail);
                                account_pw.erase(Ggmail);
                                c=-1;
                                cout<<"Account deleted Successfully"<<endl;
                                break;
                            case 13:
                                l.makespam(); 
                                cout<<"Mail marked as Spam"<<endl;
                                break;
                            case 14:
                            cout<<"****  SPAM MAILS  *****"<<endl;
                                l.displayspam();
                                break;
                            default:
                                c=-1;
                            }
                            cout<<endl;
                        }

                        break;
            }

            case 2:
            {
                signup();
                cout<<"Signup successfull!!";
                break;
            }
            
            
        
        default:
            break;
        }
    }
}