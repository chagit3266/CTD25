# SimpleImg

מבנה תיקיות של פרויקט CTD25:

```text
CTD25/
├── .vs/                          # קבצי קונפיגורציה של Visual Studio (נוצרו אוטומטית)
├── cpp/
│   ├── OpenCV_451/               # ספריית OpenCV מקומית (גרסה 4.5.1)
│   │   ├── include/
│   │   │   └── opencv2/          # כל כותרות OpenCV
│   │   │       ├── calib3d/
│   │   │       ├── core/
│   │   │       │   ├── cuda/
│   │   │       │   ├── hal/
│   │   │       │   ├── opencl/
│   │   │       │   └── ...       # +50 תיקיות נוספות
│   │   │       ├── dnn/
│   │   │       ├── features2d/
│   │   │       └── ...           # כל מודולי OpenCV
│   │   └── ...                   # קבצים בינאריים (אם קיימים)
│   │
│   ├── out/                      # קבצי build שנוצרו
│   │   └── build/
│   │       └── x64-Debug/
│   │           ├── CMakeCache.txt
│   │           └── ...           # קבצי build נוספים
│   │
│   ├── src/                      # קוד המקור שלך
│   │   ├── img.cpp               # טיפול בתמונות
│   │   ├── img.hpp
│   │   └── main.cpp              # נקודת כניסה
│   │
│   └── CMakeLists.txt            # קובץ קונפיגורציית CMake
│
├── It1_interfaces_cpp/           # ליבת המשחק
│   ├── board.cpp                 # לוח המשחק
│   ├── command.cpp               # פקודות
│   ├── game.cpp                  # לוגיקת משחק ראשית
│   ├── graphics.cpp              # גרפיקה
│   ├── piece.cpp                 # מחלקת כלי בסיס
│   ├── physics.cpp               # פיזיקת משחק
│   └── test/
│       └── board.test.cpp        # בדיקות
│
├── pieces/                       # הגדרות כלים (שחמט?)
│   ├── PB/                       # רגלי שחור (Pawn Black)
│   │   └── states/
│   │       ├── idle/
│   │       │   └── config.json   # הגדרות מצב
│   │       ├── move/
│   │       └── ...               # מצבים נוספים
│   ├── PW/                       # רגלי לבן (Pawn White)
│   ├── QB/                       # מלכה שחורה
│   └── ...                       # כלים נוספים (RB, RW, KB, KW, NW, NB)
│
├── java/                         # קוד Java (לא בשימוש נראה)
├── py/                           # קוד Python (לא בשימוש נראה)
│
├── .gitignore                    # קבצים להתעלמות ב-Git
├── board.png                     # תמונת לוח משחק לדוגמה
├── project_structure.txt         # פלט מבנה תיקיות
└── README.md                     # תיעוד
```
