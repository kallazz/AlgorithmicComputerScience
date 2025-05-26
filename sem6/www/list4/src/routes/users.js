const express = require('express');
const bcrypt = require('bcryptjs');
const { User } = require('../models/User');
const authMiddleware = require('../middleware/auth');
const adminMiddleware = require('../middleware/admin');
const router = express.Router();

router.post('/', async (req, res) => {
  try {
    const { username, email, password } = req.body;

    const user = new User({
      username,
      email,
      password,
      role: 'user'
    });

    await user.save();

    const userResponse = user.toObject();
    delete userResponse.password;
    res.status(201).json(userResponse);
  } catch (error) {
    if (error.code === 11000) {
      const field = Object.keys(error.keyPattern)[0];
      res.status(409).json({ error: `${field === 'email' ? 'Email' : 'Nazwa użytkownika'} już istnieje` });
    } else if (error.name === 'ValidationError') {
      const messages = Object.values(error.errors).map(err => err.message);
      res.status(400).json({ error: messages[0] });
    } else {
      res.status(500).json({ error: 'Błąd serwera' });
    }
  }
});

router.get('/', authMiddleware, adminMiddleware, async (req, res) => {
  try {
    const users = await User.find({}, '-password').sort({ createdAt: -1 });
    res.json(users);
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

router.get('/:id', authMiddleware, async (req, res) => {
  try {
    const { id } = req.params;

    if (req.user.role !== 'admin' && req.user._id.toString() !== id) {
      return res.status(403).json({ error: 'Brak uprawnień' });
    }

    const user = await User.findById(id, '-password');

    if (!user) {
      return res.status(404).json({ error: 'Użytkownik nieznaleziony' });
    }

    res.json(user);
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

router.put('/:id', authMiddleware, async (req, res) => {
  try {
    const { id } = req.params;
    const { username, email } = req.body;

    if (req.user.role !== 'admin' && req.user._id.toString() !== id) {
      return res.status(403).json({ error: 'Brak uprawnień' });
    }

    const user = await User.findByIdAndUpdate(
      id,
      { username, email },
      { new: true, select: '-password' }
    );

    if (!user) {
      return res.status(404).json({ error: 'Użytkownik nieznaleziony' });
    }

    res.json(user);
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

router.delete('/:id', authMiddleware, adminMiddleware, async (req, res) => {
  try {
    const { id } = req.params;
    const user = await User.findByIdAndDelete(id);
    
    if (!user) {
      return res.status(404).json({ error: 'Użytkownik nieznaleziony' });
    }

    res.status(204).send();
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

module.exports = router;