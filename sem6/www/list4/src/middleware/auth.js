const jwt = require('jsonwebtoken');
const { User } = require('../models/User');
require('dotenv').config();

const authMiddleware = async (req, res, next) => {
  const token = req.header('Authorization')?.replace('Bearer ', '');
  if (!token) {
    return res.status(401).json({ error: 'Brak tokenu dostępu' });
  }

  try {
    const decoded = jwt.verify(token, process.env.JWT_SECRET, { algorithms: ['HS512'] });
    const user = await User.findById(decoded.userId);
    if (!user) {
      return res.status(401).json({ error: 'Użytkownik nieznaleziony' });
    }
    req.user = user;
    next();
  } catch (error) {
    res.status(401).json({ error: 'Nieprawidłowy token' });
  }
};

module.exports = authMiddleware;