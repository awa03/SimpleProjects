import random

def generate_and_append_random_numbers(n, filename):
    with open(filename, 'a') as file:
        for _ in range(n):
            random_number = random.randint(1, 10000)
            file.write(str(random_number) + ' ')

if __name__ == "__main__":
    try:
        n = int(input("Enter the number of million random numbers to generate: "))
        filename = input("Enter the file name to append random numbers: ")

        generate_and_append_random_numbers(n, filename)
        print(f"{n} million random numbers appended to {filename}")
    
    except ValueError:
        print("Invalid input. Please enter a valid number.")
    except Exception as e:
        print(f"An error occurred: {e}")
