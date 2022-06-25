#include "functions.hpp"

// from project example
struct FileHeader {
    short bfType;
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
} File;

// from project example
struct PictureHeader {
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
} Picture;

// from project example
void readFile(string path)
{
    FILE* f = fopen(&path[0], "rb");

    if(f == nullptr)
    {
        cerr << "Error with opening the file";
    }
    else
    {
        cout << "INFORMACJE O BITMAPIE" << endl << endl;

        fread(&File.bfType, sizeof(File.bfType), 1, f);
        cout << "Typ: " << hex << static_cast<int>(File.bfType) << endl;

        fread(&File.bfSize, sizeof(File.bfSize), 1, f);
        cout << "Rozmiar pliku: " << dec << File.bfSize << " bajtow" << endl;

        fread(&File.bfReserved1, sizeof(File.bfReserved1), 1, f);
        cout << "Zarezerwowane1: " << File.bfReserved1 << endl;

        fread(&File.bfReserved2, sizeof(File.bfReserved2), 1, f);
        cout << "Zarezerwowane2: "<< File.bfReserved2 << endl;

        fread(&File.bfOffBits, sizeof(File.bfOffBits), 1, f);
        cout << "Pozycja danych obrazu: " << File.bfOffBits << endl << endl;

        fseek(f, 14, SEEK_SET);
        fread(&Picture.biSize, sizeof(Picture.biSize), 1, f);
        cout << "Wielkosc naglowka informacyjnego: " << Picture.biSize << endl;

        fread(&Picture.biWidth, sizeof(Picture.biWidth), 1, f);
        cout << "Szerokosc: " << Picture.biWidth << " pikseli" << endl;

        fread(&Picture.biHeight, sizeof(Picture.biHeight), 1, f);
        cout << "Wysokosc: " << Picture.biHeight << " pikseli" << endl;

        fread(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, f);
        cout << "Liczba platow: " << Picture.biPlanes << endl;

        fread(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, f);
        cout << "Liczba bitow na piksel: " << Picture.biBitCount << " (1, 4, 8, or 24)" << endl;

        fread(&Picture.biCompression, sizeof(Picture.biCompression), 1, f);
        cout << "Kompresja: " << Picture.biCompression << " (0=none, 1=RLE-8, 2=RLE-4)" << endl;

        fread(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, f);
        cout << "Rozmiar samego rysunku: " << Picture.biSizeImage << endl;

        fread(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, f);
        cout << "Rozdzielczosc pozioma: " << Picture.biXPelsPerMeter << endl;

        fread(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, f);
        cout << "Rozdzielczosc pionowa: " << Picture.biYPelsPerMeter << endl;

        fread(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, f);
        cout << "Liczba kolorow w palecie: " << Picture.biClrUsed << endl;

        fread(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, f);
        cout << "Wazne kolory w palecie: " << Picture.biClrImportant << endl;

        FILE* w = fopen("negative.bmp", "wb");
        if (w == nullptr)
        {
            cerr << "Can't open the file!";
        }
        else
        {
            cout << "File w opened" << endl;

            fseek(w, 0, SEEK_SET);
            fwrite(&File.bfType, sizeof(File.bfType), 1, w);
            fwrite(&File.bfSize, sizeof(File.bfSize), 1, w);
            fwrite(&File.bfReserved1, sizeof(File.bfReserved1), 1, w);
            fwrite(&File.bfReserved2, sizeof(File.bfReserved2), 1, w);
            fwrite(&File.bfOffBits, sizeof(File.bfOffBits), 1, w);

            fseek(w, 14, SEEK_SET);
            fwrite(&Picture.biSize, sizeof(Picture.biSize), 1, w);
            fwrite(&Picture.biWidth, sizeof(Picture.biWidth), 1, w);
            fwrite(&Picture.biHeight, sizeof(Picture.biHeight), 1, w);
            fwrite(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, w);
            fwrite(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, w);
            fwrite(&Picture.biCompression, sizeof(Picture.biCompression), 1, w);
            fwrite(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, w);
            fwrite(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, w);
            fwrite(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, w);
            fwrite(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, w);
            fwrite(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, w);

            fseek(w, sizeof(File.bfOffBits), SEEK_SET);

            int bmpImg;
            for (int i = File.bfOffBits; i < File.bfSize; i++)
            {
                fseek(f, i, SEEK_SET);
                fseek(w, i, SEEK_SET);
                fread(&bmpImg, 3, 1, f);
                bmpImg = INT_MAX - bmpImg; //Tworzymy negatyw
                fwrite(&bmpImg, 3, 1, w);
            }
            fclose(w);
            fclose(f);
        }
    }
}
