import Router from "express";
import { requireAuth } from "../middleware/authMiddleware.js";
import { settings_get, settings_post } from "../controllers/settingsController.js";

const router = Router();

router.get("/settings", requireAuth, settings_get);
router.post("/settings", requireAuth, settings_post);

export default router;