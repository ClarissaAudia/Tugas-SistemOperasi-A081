#include <iostream>
#include <pthread.h>

using namespace std;

// Data nilai mahasiswa
int nilai[] = {80, 75, 90, 65, 85};

// Mutex
pthread_mutex_t mutex;

// THREAD 1
void* thread1(void* arg)
{
    int total = 0;

    for (int i = 0; i < 5; i++)
    {
        total = total + nilai[i];
    }

    // Mengunci akses ke output
    pthread_mutex_lock(&mutex);

    cout << "Total nilai: " << total << endl;

    // Membuka kembali mutex
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// THREAD 2
void* thread2(void* arg)
{
    int tertinggi = 0;

    for (int i = 0; i < 5; i++)
    {
        if (nilai[i] > tertinggi)
        {
            tertinggi = nilai[i];
        }
    }

    // Mengunci akses ke output
    pthread_mutex_lock(&mutex);

    cout << "Nilai tertinggi: " << tertinggi << endl;

    // Membuka kembali mutex
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// THREAD 3
void* thread3(void* arg)
{
    int jumlahLulus = 0;

    for (int i = 0; i < 5; i++)
    {
        if (nilai[i] >= 70)
        {
            jumlahLulus++;
        }
    }

    // Mengunci akses ke output
    pthread_mutex_lock(&mutex);

    cout << "Jumlah mahasiswa yang lulus: " << jumlahLulus << endl;

    // Membuka kembali mutex
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    // Deklarasi thread
    pthread_t thread1_id;
    pthread_t thread2_id;
    pthread_t thread3_id;

    // Inisialisasi mutex
    pthread_mutex_init(&mutex, NULL);

    // Membuat Thread 1
    pthread_create(&thread1_id, NULL, thread1, NULL);

    // Membuat Thread 2
    pthread_create(&thread2_id, NULL, thread2, NULL);

    // Membuat Thread 3
    pthread_create(&thread3_id, NULL, thread3, NULL);

    // Menunggu Thread 1 selesai
    pthread_join(thread1_id, NULL);

    // Menunggu Thread 2 selesai
    pthread_join(thread2_id, NULL);

    // Menunggu Thread 3 selesai
    pthread_join(thread3_id, NULL);

    // Menghancurkan mutex
    pthread_mutex_destroy(&mutex);

    cout << "Program selesai." << endl;

    return 0;
}