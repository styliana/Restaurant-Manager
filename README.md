# Restaurant Manager
to aplikacja okienkowa stworzona w języku C++ z użyciem frameworka Qt, dedykowana wspomaganiu zarządzania zamówieniami w restauracji. Umożliwia łatwe aktualizowanie menu i przechowywanie zamówień w pliku tekstowym, co zapewnia trwałość danych oraz ułatwia podgląd aktualnych zamówień. Intuicyjny interfejs użytkownika umożliwia efektywne zarządzanie zamówieniami klientów.

Aplikacja skupia się głównie na dodawaniu nowych zamówień, oferując obsługę pełną kontrolę nad nimi poprzez dodawanie i usuwanie istniejących. Struktura aplikacji obejmuje główny moduł Restaurant Manager oraz bibliotekę DLL, z odpowiednimi plikami nagłówkowymi i źródłowymi.

Zastosowane funkcje w klasie RestaurantApp obejmują:
  * inicjalizację interfejsu użytkownika,
  * wczytywanie danych z plików do tabeli,
  * dodawanie i usuwanie zamówień (z tabeli oraz z pliku),
  * odświeżanie tabeli zamówień.

Interfejs użytkownika prezentuje tabelę MENU i ORDERS, z danymi wczytanymi z plików.

Klasa OrderForm obsługuje formularz zamówienia:
  * umożliwiający wybór potraw z menu,
  * dodawanie ich do zamówienia,
  * złożenie zamówienia,
  * obliczanie całkowitej ceny.


<p align="center">
  <img src="https://github.com/styliana/Restaurant-Manager/assets/64647649/d484de16-25c2-4c8c-b568-7cfe4581144e" alt="Image" width="800" />
</p>

Okienko z formularzem OrderForm:
<p align="center">
  <img src="https://github.com/styliana/Restaurant-Manager/assets/64647649/20fc380e-3ad9-4447-8f7d-056137dd9e3c" alt="Image" width="270" />
  <img src="https://github.com/styliana/Restaurant-Manager/assets/64647649/c744c966-616b-489d-b46d-13db771463ac" alt="Image" width="300" />
  <img src="https://github.com/styliana/Restaurant-Manager/assets/64647649/9d7c6a5c-b604-4028-b893-29f76f573fc2" alt="Image" width="270" />
</p>

Obsługiwane są również wyjątki, takie jak niepoprawne dane, zbyt duża ilość dań w zamówieniu czy puste zamówienie.
<p align="center">
  <img src="https://github.com/styliana/Restaurant-Manager/assets/64647649/0e957469-16ac-4eec-b03c-7351402d4f64" alt="Image" width="250" />
  <img src="https://github.com/styliana/Restaurant-Manager/assets/64647649/005fceec-e0a6-4ccf-b06a-7cc3c7d1971f" alt="Image" width="250" />
  <img src="https://github.com/styliana/Restaurant-Manager/assets/64647649/3f03c1a1-6f88-4ef6-9dc3-a2ab3aaed772" alt="Image" width="250" />
</p>

