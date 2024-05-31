Restaurant Manager to aplikacja okienkowa stworzona w języku C++ z użyciem frameworka Qt, dedykowana wspomaganiu zarządzania zamówieniami w restauracji. Umożliwia łatwe aktualizowanie menu i przechowywanie zamówień w pliku tekstowym, co zapewnia trwałość danych oraz ułatwia podgląd aktualnych zamówień. Intuicyjny interfejs użytkownika umożliwia efektywne zarządzanie zamówieniami klientów.

Aplikacja skupia się głównie na dodawaniu nowych zamówień, oferując obsługę pełną kontrolę nad nimi poprzez edycję i usuwanie istniejących. Struktura aplikacji obejmuje główny moduł Restaurant Manager oraz bibliotekę DLL, z odpowiednimi plikami nagłówkowymi i źródłowymi.

Zastosowane funkcje w klasie RestaurantApp obejmują inicjalizację interfejsu użytkownika, wczytywanie danych z plików, dodawanie i usuwanie zamówień oraz odświeżanie tabeli zamówień. Klasa OrderForm obsługuje formularz zamówienia, umożliwiając wybór potraw z menu, dodawanie ich do zamówienia oraz obliczanie całkowitej ceny.

Interfejs użytkownika prezentuje tabelę MENU i ORDERS, z danymi wczytanymi z plików. Formularz zamówienia pozwala na wybór potraw z menu, dodanie ich do zamówienia i złożenie zamówienia. Obsługiwane są również wyjątki, takie jak niepoprawne dane czy puste zamówienie.
