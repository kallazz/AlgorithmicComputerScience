const express = require('express');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const { User } = require('../models/User');
require('dotenv').config();
const router = express.Router();

// Logowanie
router.post('/login', async (req, res) => {
  try {
    const { email, password } = req.body;

    const user = await User.findOne({ email });

    if (!email || !password || !user || !await user.comparePassword(password)) {
      return res.status(401).json({ error: 'Nieprawidłowe dane logowania' });
    }

    const token = jwt.sign({ userId: user._id }, process.env.JWT_SECRET, { expiresIn: '24h' });
    
    const userResponse = user.toObject();
    delete userResponse.password;
    
    res.json({ token, user: userResponse });
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

module.exports = router;
