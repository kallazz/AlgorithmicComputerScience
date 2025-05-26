const express = require('express');
const { Book } = require('../models/Book');
const authMiddleware = require('../middleware/auth');
const adminMiddleware = require('../middleware/admin');
const router = express.Router();

router.post('/', authMiddleware, adminMiddleware, async (req, res) => {
  try {
    const { title, author, isbn, description, published_year } = req.body;
    
    if (!title || !author || !isbn) {
      return res.status(400).json({ error: 'Tytuł, autor i ISBN są wymagane' });
    }

    const book = new Book({
      title,
      author,
      isbn,
      description,
      published_year
    });

    await book.save();
    res.status(201).json(book);
  } catch (error) {
    if (error.code === 11000) {
      res.status(409).json({ error: 'Książka z tym ISBN już istnieje' });
    } else {
      res.status(500).json({ error: 'Błąd serwera' });
    }
  }
});

router.get('/', async (req, res) => {
  try {
    const page = parseInt(req.query.page) || 1;
    const limit = parseInt(req.query.limit) || 10;
    const skip = (page - 1) * limit;
    const sortBy = req.query.sortBy || 'title';
    const sortOrder = req.query.sortOrder === 'DESC' ? -1 : 1;
    const author = req.query.author;
    const year = req.query.year;

    let filter = {};
    
    if (author) {
      filter.author = { $regex: author, $options: 'i' };
    }
    
    if (year) {
      filter.published_year = parseInt(year);
    }

    const sortObj = {};
    sortObj[sortBy] = sortOrder;

    const [books, totalBooks] = await Promise.all([
      Book.find(filter).sort(sortObj).skip(skip).limit(limit),
      Book.countDocuments(filter)
    ]);

    const totalPages = Math.ceil(totalBooks / limit);

    res.json({
      books,
      pagination: {
        currentPage: page,
        totalPages,
        totalBooks,
        hasNext: page < totalPages,
        hasPrev: page > 1
      }
    });
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

router.get('/:id', async (req, res) => {
  try {
    const { id } = req.params;
    const book = await Book.findById(id);
    
    if (!book) {
      return res.status(404).json({ error: 'Książka nieznaleziona' });
    }

    res.json(book);
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

router.put('/:id', authMiddleware, adminMiddleware, async (req, res) => {
  try {
    const { id } = req.params;
    const { title, author, isbn, description, published_year } = req.body;

    const book = await Book.findByIdAndUpdate(
      id,
      { title, author, isbn, description, published_year },
      { new: true }
    );

    if (!book) {
      return res.status(404).json({ error: 'Książka nieznaleziona' });
    }

    res.json(book);
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

router.delete('/:id', authMiddleware, adminMiddleware, async (req, res) => {
  try {
    const { id } = req.params;
    const book = await Book.findByIdAndDelete(id);
    
    if (!book) {
      return res.status(404).json({ error: 'Książka nieznaleziona' });
    }

    res.status(204).send();
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

module.exports = router;