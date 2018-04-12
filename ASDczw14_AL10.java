

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Comparator;
import java.util.PriorityQueue;

class Wezel {

	int czestotliwosc;
	char znak;
	Wezel lewy;
	Wezel prawy;
}

//klasa komparator pomaga porownac wezel na podstawie atrybutu frequence
class Komparator implements Comparator<Wezel> {
	public int compare(Wezel x, Wezel y) {
		return x.czestotliwosc - y.czestotliwosc;
	}
}

public class Huffman {
	
	static int poKodowaniu;

	//rekursywna funkcja do tworzenia kodu huffmana
	public static void drukuj(Wezel korzen, String s) {
		

		//jesli lewy i prawy sa nullami to drukujemy kod
		if (korzen.lewy == null && korzen.prawy == null) {
			System.out.println(korzen.znak + " - " + s + " - " + korzen.czestotliwosc);
			poKodowaniu += s.length() * korzen.czestotliwosc;
			return;
		}

		// jesli idziemy w lewo to dodajemy 0, jesli w prawo to 1

		//rekursja
		drukuj(korzen.lewy, s + "0");
		drukuj(korzen.prawy, s + "1");
	}

	public static void main(String[] args) {
		// 26 to ilosc liter w alfabecie
		int n = 26;
		int ascii = 97; // 97 == a w ascii
		char[] charArray = new char[26];
		int[] charfreq = new int[26];

		File file = new File("file.txt");
		BufferedReader reader = null;
		//tworzymy tablice liter jakie s¹ w pliku oraz czêstotliwoœæ ich wystêpowania
		try {
			reader = new BufferedReader(new FileReader(file));
			int text;

			while ((text = reader.read()) != -1) {
				if (text >= 'a' && text <= 'z') {
					charArray[text - ascii] = (char) text;
					charfreq[text - ascii]++;
				}
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (reader != null) {
					reader.close();
				}
			} catch (IOException e) {
			}
		}

		// tworzymy kolejke priorytetowa do zbudowania ExtractMin
		PriorityQueue<Wezel> kolejka = new PriorityQueue<Wezel>(n, new Komparator());

		for (int i = 0; i < n; i++) {

			//tworzymy obiekt wezla i dodajemy do kolejki
			Wezel w = new Wezel();
			
			w.lewy = null;
			w.prawy = null;
			w.znak = charArray[i];
			w.czestotliwosc = charfreq[i];


			if (charfreq[i] > 0) {
				kolejka.add(w);
			}
		}

		// tworzymy nowy wezel
		Wezel wezel = null;

		// tutaj bierzemy dwie najmniejsze wartosci
		while (kolejka.size() > 1) {

			// pierwsza
			Wezel x = kolejka.poll(); //bierzemy pierwszy element z kolejki i usuwamy

			// druga
			Wezel y = kolejka.poll(); //bierzemy pierwszy element z kolejki i usuwamy

			// nowy wezel
			Wezel z = new Wezel();

			// sume czestotliwosci dwoch wezlow przypisujemy do trzeciego
			z.czestotliwosc = x.czestotliwosc + y.czestotliwosc;

			// pierwszy wezel to lewy syn
			z.lewy = x;

			// drugi wezel to prawy syn
			z.prawy = y;

			// wezel z to tymczasowy wezel glowny
			wezel = z;

			// dodajemy tymczasowy wezel glowny do kolejki
			kolejka.add(z);
		}

		//drukowanie
		System.out.println("KODY HUFFMANA: ");
		drukuj(wezel, "");
		System.out.println("PRZED KODOWANIEM: " + wezel.czestotliwosc);
		System.out.println("PO KODOWANIU: " + poKodowaniu);
	}
}