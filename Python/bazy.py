import psycopg2
import pandas as pd
import numpy as np
import sklearn.model_selection as sm
from sklearn.ensemble import RandomForestRegressor
from sklearn.externals import joblib
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.metrics import classification_report
try:
    conn = psycopg2.connect(user="stud",
                            password="stud",
                            host="158.75.112.103",
                            port="55655",
                            database="stud")
    kursor = conn.cursor()
    kursor.execute("Select version();")
    r = kursor.fetchone()
    #print (r)
    kursor.execute("Select * From Dzialy")
    r2 = kursor.fetchall()
    #print (str(r2) + "\n")
    kursor.execute("Select * From Pracownicy")
    r3 = kursor.fetchmany(10)
    #print (str(r3) + "\n")
    kursor.execute("Insert Into Pracownicy Values(110,'cos','tam', 5, 5, 'ct')")
    kursor.query
    sql = "Select pensja From Pracownicy where nazwisko=%s"
    kursor.execute(sql, ('Potter',))
    #print (kursor.rowcount)
    #print (kursor.query)

    sql2 = "Select * from Pracownicy"
    ramka = pd.read_sql_query(sql2, conn)
    ramka = ramka.drop(['id','imie','nazwisko'],axis = 1);
    #print (ramka)
    #print (ramka.describe())
    #print (ramka.corr())
    nowy = ramka.fillna(value=0)
    ramka.fillna(value=0, inplace=True)
    #print (nowy.describe())
    dane = pd.get_dummies(ramka)
    #print dane.describe()
    #print dane.corr()
    #export_excel = ramka.to_excel(r'dane.xlsx')

    wynikowe = np.array(dane['id_dzialu'])
    sasiedzi = np.copy(wynikowe)

    wynikowe[wynikowe < 4] = 0
    wynikowe[wynikowe > 3] = 1

    parametry = np.array(dane.drop('id_dzialu',axis = 1))
    szkol_parametr,test_parametr,szkol_wyn,test_wyn = sm.train_test_split(parametry,wynikowe,test_size=0.3,random_state=42);
    #print szkol_wyn.shape,szkol_parametr.shape,test_wyn.shape,test_parametr.shape
    rf = RandomForestRegressor(n_estimators=50,random_state=42)
    rf.fit(szkol_parametr,szkol_wyn)
    joblib.dump(rf,'plikLasu.sav')
    # Wczytywanie
    #gdzie = joblib.load(plik)

    oblicz = rf.predict(test_parametr)
    print oblicz
    #print oblicz.shape
    #print test_wyn

    #print confusion_matrix(test_wyn, oblicz)
    #print accuracy_score(test_wyn,oblicz)
    #print classification_report(test_wyn,oblicz)

    conn.close()
except (Exception, psycopg2.Error) as error:
    print "Blad\n", error


