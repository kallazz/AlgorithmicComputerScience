import database from "../database.js";

export async function getTagNameById(id) {
    const [result] = await database.execute(
        "SELECT tag_name FROM tags WHERE id = ?",
        [id]
    );
    const tagName = result[0];
    return tagName;
};

export async function getAllTags() {
    const [tags] = await database.execute(
        "SELECT * FROM tags ORDER BY tag_name"
    );
    return tags;
};