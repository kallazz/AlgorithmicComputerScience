const request = require('supertest');
const { Book } = require('../src/models/Book');

describe('Books Routes', () => {
  let admin, user, adminToken, userToken;

  beforeEach(async () => {
    admin = await createTestAdmin();
    user = await createTestUser();
    adminToken = generateAuthToken(admin._id);
    userToken = generateAuthToken(user._id);
  });

  describe('POST /api/books - Add Book (Admin only)', () => {
    it('should allow admin to add book', async () => {
      const bookData = {
        title: 'Test Book',
        author: 'Test Author',
        isbn: '978-3-16-148410-0',
        description: 'Test description',
        published_year: 2023
      };

      const response = await request(app)
        .post('/api/books')
        .set('Authorization', `Bearer ${adminToken}`)
        .send(bookData);

      expect(response.status).toBe(201);
      expect(response.body.title).toBe(bookData.title);
      expect(response.body.author).toBe(bookData.author);
      expect(response.body.isbn).toBe(bookData.isbn);
    });

    it('should reject non-admin book creation', async () => {
      const bookData = {
        title: 'Test Book',
        author: 'Test Author',
        isbn: '978-3-16-148410-0'
      };

      const response = await request(app)
        .post('/api/books')
        .set('Authorization', `Bearer ${userToken}`)
        .send(bookData);

      expect(response.status).toBe(403);
      expect(response.body.error).toBe('Brak uprawnień administratora');
    });

    it('should reject book without required fields', async () => {
      const response = await request(app)
        .post('/api/books')
        .set('Authorization', `Bearer ${adminToken}`)
        .send({
          title: 'Test Book'
          // brak author i isbn
        });

      expect(response.status).toBe(400);
      expect(response.body.error).toBe('Tytuł, autor i ISBN są wymagane');
    });

    it('should reject duplicate ISBN', async () => {
      const bookData = {
        title: 'First Book',
        author: 'Author One',
        isbn: '978-3-16-148410-0'
      };

      // Dodaj pierwszą książkę
      await request(app)
        .post('/api/books')
        .set('Authorization', `Bearer ${adminToken}`)
        .send(bookData);

      // Spróbuj dodać książkę z tym samym ISBN
      const response = await request(app)
        .post('/api/books')
        .set('Authorization', `Bearer ${adminToken}`)
        .send({
          title: 'Second Book',
          author: 'Author Two',
          isbn: '978-3-16-148410-0'
        });

      expect(response.status).toBe(409);
      expect(response.body.error).toBe('Książka z tym ISBN już istnieje');
    });

    it('should reject unauthenticated request', async () => {
      const response = await request(app)
        .post('/api/books')
        .send({
          title: 'Test Book',
          author: 'Test Author',
          isbn: '978-3-16-148410-0'
        });

      expect(response.status).toBe(401);
    });
  });

  describe('GET /api/books - List Books', () => {
    beforeEach(async () => {
      // Dodaj testowe książki
      const books = [
        { title: 'Book A', author: 'Author X', isbn: '111', published_year: 2020 },
        { title: 'Book B', author: 'Author Y', isbn: '222', published_year: 2021 },
        { title: 'Book C', author: 'Author X', isbn: '333', published_year: 2022 }
      ];

      for (const book of books) {
        await new Book(book).save();
      }
    });

    it('should return books list without authentication', async () => {
      const response = await request(app)
        .get('/api/books');

      expect(response.status).toBe(200);
      expect(response.body.books).toHaveLength(3);
      expect(response.body.pagination).toBeDefined();
      expect(response.body.pagination.totalBooks).toBe(3);
    });

    it('should support pagination', async () => {
      const response = await request(app)
        .get('/api/books?page=1&limit=2');

      expect(response.status).toBe(200);
      expect(response.body.books).toHaveLength(2);
      expect(response.body.pagination.currentPage).toBe(1);
      expect(response.body.pagination.totalPages).toBe(2);
      expect(response.body.pagination.hasNext).toBe(true);
      expect(response.body.pagination.hasPrev).toBe(false);
    });

    it('should support author filtering', async () => {
      const response = await request(app)
        .get('/api/books?author=Author X');

      expect(response.status).toBe(200);
      expect(response.body.books).toHaveLength(2);
      expect(response.body.books.every(book => book.author === 'Author X')).toBe(true);
    });

    it('should support year filtering', async () => {
      const response = await request(app)
        .get('/api/books?year=2021');

      expect(response.status).toBe(200);
      expect(response.body.books).toHaveLength(1);
      expect(response.body.books[0].published_year).toBe(2021);
    });

    it('should support sorting', async () => {
      const response = await request(app)
        .get('/api/books?sortBy=published_year&sortOrder=DESC');

      expect(response.status).toBe(200);
      const years = response.body.books.map(book => book.published_year);
      expect(years).toEqual([2022, 2021, 2020]);
    });

    it('should handle empty results', async () => {
      const response = await request(app)
        .get('/api/books?author=NonExistent');

      expect(response.status).toBe(200);
      expect(response.body.books).toHaveLength(0);
      expect(response.body.pagination.totalBooks).toBe(0);
    });
  });

  describe('GET /api/books/:id - Get Single Book', () => {
    let testBook;

    beforeEach(async () => {
      testBook = await new Book({
        title: 'Test Book',
        author: 'Test Author',
        isbn: '978-3-16-148410-0',
        description: 'Test description'
      }).save();
    });

    it('should return single book', async () => {
      const response = await request(app)
        .get(`/api/books/${testBook._id}`);

      expect(response.status).toBe(200);
      expect(response.body._id).toBe(testBook._id.toString());
      expect(response.body.title).toBe(testBook.title);
    });

    it('should return 404 for non-existent book', async () => {
      const nonExistentId = '507f1f77bcf86cd799439011';
      const response = await request(app)
        .get(`/api/books/${nonExistentId}`);

      expect(response.status).toBe(404);
      expect(response.body.error).toBe('Książka nie znaleziona');
    });

    it('should handle invalid ObjectId', async () => {
      const response = await request(app)
        .get('/api/books/invalid-id');

      expect(response.status).toBe(500);
    });
  });

  describe('PUT /api/books/:id - Update Book (Admin only)', () => {
    let testBook;

    beforeEach(async () => {
      testBook = await new Book({
        title: 'Original Title',
        author: 'Original Author',
        isbn: '978-3-16-148410-0'
      }).save();
    });

    it('should allow admin to update book', async () => {
      const updateData = {
        title: 'Updated Title',
        author: 'Updated Author',
        description: 'Updated description'
      };

      const response = await request(app)
        .put(`/api/books/${testBook._id}`)
        .set('Authorization', `Bearer ${adminToken}`)
        .send(updateData);

      expect(response.status).toBe(200);
      expect(response.body.title).toBe(updateData.title);
      expect(response.body.author).toBe(updateData.author);
      expect(response.body.description).toBe(updateData.description);
    });

    it('should reject non-admin update', async () => {
      const response = await request(app)
        .put(`/api/books/${testBook._id}`)
        .set('Authorization', `Bearer ${userToken}`)
        .send({ title: 'Hacked Title' });

      expect(response.status).toBe(403);
      expect(response.body.error).toBe('Brak uprawnień administratora');
    });

    it('should return 404 for non-existent book', async () => {
      const nonExistentId = '507f1f77bcf86cd799439011';
      const response = await request(app)
        .put(`/api/books/${nonExistentId}`)
        .set('Authorization', `Bearer ${adminToken}`)
        .send({ title: 'Updated Title' });

      expect(response.status).toBe(404);
      expect(response.body.error).toBe('Książka nie znaleziona');
    });
  });

  describe('DELETE /api/books/:id - Delete Book (Admin only)', () => {
    let testBook;

    beforeEach(async () => {
      testBook = await new Book({
        title: 'Book to Delete',
        author: 'Author',
        isbn: '978-3-16-148410-0'
      }).save();
    });

    it('should allow admin to delete book', async () => {
      const response = await request(app)
        .delete(`/api/books/${testBook._id}`)
        .set('Authorization', `Bearer ${adminToken}`);

      expect(response.status).toBe(204);

      // Sprawdź czy książka została usunięta
      const deletedBook = await Book.findById(testBook._id);
      expect(deletedBook).toBeNull();
    });

    it('should reject non-admin deletion', async () => {
      const response = await request(app)
        .delete(`/api/books/${testBook._id}`)
        .set('Authorization', `Bearer ${userToken}`);

      expect(response.status).toBe(403);
      expect(response.body.error).toBe('Brak uprawnień administratora');
    });

    it('should return 404 for non-existent book', async () => {
      const nonExistentId = '507f1f77bcf86cd799439011';
      const response = await request(app)
        .delete(`/api/books/${nonExistentId}`)
        .set('Authorization', `Bearer ${adminToken}`);

      expect(response.status).toBe(404);
      expect(response.body.error).toBe('Książka nie znaleziona');
    });
  });
});